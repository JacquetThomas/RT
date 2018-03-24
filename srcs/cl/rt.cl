/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.cl                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 15:20:24 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/17 16:52:21 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"
#include "light.cl"
#include "texture.cl"
#include "collision.cl"
#include "reflection.cl"
#include "depth_of_field.cl"

static void		put_pixel(__global uint* pixels, const int2 pixel, const int2 size, const int color, const t_ray ray, __global t_rt *rt)
{
	if (rt->offset == 0)
		pixels[(pixel.x - rt->offset) + pixel.y * size.x] = color;
	else
		pixels[((pixel.x - rt->offset) / (rt->nb_cli + 1)) + (pixel.y * size.x / (rt->nb_cli + 1))] = color;
}

static t_ray	ft_init_ray(__global t_rt *rt, const double2 coords, const int2 size)
{
	t_ray			ray;
	const double	a = (WIN_W - ((double)(coords.x + 546) * rt->eye.fov)) / \
																		WIN_H;
	const double	b = (WIN_H - ((double)(coords.y + 109) * (rt->eye.fov * \
													rt->eye.aspect))) / WIN_W;

	ray.id = -1;
	ray.t = 200000.0;
	ray.dist = 200000.0;
	ray.bounces = MAX_BOUNCES;
	ray.dir = normalize((t_vector){
		a * rt->m[1].x + b * rt->m[2].x + rt->eye.zoom * rt->m[0].x, \
		a * rt->m[1].y + b * rt->m[2].y + rt->eye.zoom * rt->m[0].y, \
		a * rt->m[1].z + b * rt->m[2].z + rt->eye.zoom * rt->m[0].z \
	});
	ray.pos = rt->eye.pos;
	return (ray);
}

static t_color	ft_color(__global t_rt *rt, const t_ray ray, const double l, __constant double *rand)
{
	t_color	c;
	int		color = (ray.id < rt->nb_obj) ? rt->objects[ray.id].color.c : -1;

	if (color != -1 && rt->objects[ray.id].p_texture != 0 && rt->config.effects)
		color = ft_procedural_texture(rt, ray, &rt->objects[ray.id], rand).c;
	c.b = min(max(min(max((color >> 16 & 0xff) * (l * BL), 0.0), 255.0) + \
						min(max(220.0 * (l - 1.0), 0.0), 255.0), 0.0), 255.0);
	c.g = min(max(min(max((color >> 8 & 0xff) * (l * GL), 0.0), 255.0) + \
						min(max(244.0 * (l - 1.0), 0.0), 255.0), 0.0), 255.0);
	c.r = min(max(min(max((color & 0xff) * (l * RL), 0.0), 255.0) + \
						min(max(255.0 * (l - 1.0), 0.0), 255.0), 0.0), 255.0);
	c.c = 0xff << 24 | c.b << 16 | c.g << 8 | c.r;
	return (c);
}

t_color ft_get_color_per_ray(const double2 aa_coords, const int2 size, __global t_rt *rt, __constant double *rand)
{
	t_ray		ray;
	t_object	obj;
	t_color		color = {0, 0, 0, 0};

	ray = ft_init_ray(rt, aa_coords, size);
	ft_check_collisions(rt, &ray);
	obj = rt->objects[ray.id];
	if (rt->config.dof && rt->config.effects && aa_coords.x <= size.x)
		color = ft_depth_of_field(rt, rand, size, aa_coords);
	else if (rt->config.effects && (rt->objects[ray.id].reflect || rt->objects[ray.id].transp) && ray.id != -1)
		color = ft_reflection(rt, &ray, rand);
	else if (rt->config.show_focus && rt->config.dof)
		color = ft_focus_plane(rt, &ray, rand);
	else if (ray.id != -1)
		color = ft_color(rt, ray, ft_light(rt, &ray, rand), rand);
	else
		color = (t_color){0, 0, 0, 0};
	return (color);
}

t_color ft_anti_aliasing(const int2	coords, __global t_rt *rt, __constant double *rand, const int2	size)
{
	t_color			color = {0, 0, 0, 0};
	t_color			color_for_now = {0, 0, 0, 0};
	double2			aa_coords;
	int				i = 1;
	int				j = 1;
	const int		aa_points = rt->config.aa / 4;
	const double	aa_coef = 0.5 / (aa_points + 1);

	while (i <= 4)
	{
		j = 1;
		while (j <= aa_points)
		{
			if (i == 1)
				aa_coords = (double2){coords.x + j * aa_coef, coords.y + (0.5 - j * aa_coef)};
			else if (i == 2)
				aa_coords = (double2){coords.x + 0.5 + j * aa_coef, coords.y + j * aa_coef};
			else if (i == 3)
				aa_coords = (double2){coords.x + 0.5 + j * aa_coef, coords.y + 0.5 + (0.5 - j * aa_coef)};
			else
				aa_coords = (double2){coords.x + j * aa_coef, coords.y + 0.5 + j * aa_coef};
			color_for_now = ft_get_color_per_ray(aa_coords, size, rt, rand);
			color.r += color_for_now.r;
			color.g += color_for_now.g;
			color.b += color_for_now.b;
			j++;
		}
		i++;
	}
	color.r /= rt->config.aa;
	color.g /= rt->config.aa;
	color.b /= rt->config.aa;
	color.c = 0xff << 24 | color.b << 16 | color.g << 8 | color.r;
	return (color);
}

__kernel void	core(__global uint *pixels, __global t_rt *rt, __constant double *rand)
{
	const int2	size = {(int)get_global_size(GLOBAL_X), \
												(int)get_global_size(GLOBAL_Y)};
	const int2	coords = {(int)get_global_id(GLOBAL_X) * (rt->nb_cli + 1) + rt->offset, \
												(int)get_global_id(GLOBAL_Y)};
	double2		coordsinitray = (double2){coords.x, coords.y};
	t_ray		ray = ft_init_ray(rt, coordsinitray, size);
	t_object	obj;
	int			color;

	if (rt->config.aa > 1 && rt->config.effects && coords.x <= size.x)
		color = ft_anti_aliasing(coords, rt, rand, size).c;
	else if ((rt->config.dof && !rt->config.aa) && rt->config.effects && coords.x <= size.x)
		color = ft_depth_of_field(rt, rand, size, coordsinitray).c;
	else if (coords.x <= size.x)
	{
		ft_check_collisions(rt, &ray);
		obj = rt->objects[ray.id];
		if (rt->config.effects && (rt->objects[ray.id].reflect || rt->objects[ray.id].transp) && ray.id != -1)
			color = ft_reflection(rt, &ray, rand).c;
		else if (rt->config.show_focus && rt->config.dof)
			color = ft_focus_plane(rt, &ray, rand).c;
		else if (ray.id != -1)
			color = ft_color(rt, ray, ft_light(rt, &ray, rand), rand).c;
		else
			color = 0xff000000;
	}
	if (coords.x <= size.x)
		put_pixel(pixels, coords, size, color, ray, rt);
}
