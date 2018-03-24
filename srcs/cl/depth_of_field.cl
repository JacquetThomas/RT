/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_of_field.cl                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 16:21:27 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/08 19:03:12 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static t_ray	ft_random_ray(t_ray *ray, __global t_rt *rt, __constant double *rand, const int i, const double2 coords)
{
	 const double	r1 = fmod(rand[i % MAX_RAND], 1.0) - .5;
	 const double	r2 = fmod(rand[(i + 1) % MAX_RAND], 1.0) - .5;
	 const double	d = (dot(-rt->eye.rot, rt->config.focus) - dot(-rt->eye.rot, ray->pos)) / dot(-rt->eye.rot, ray->dir);
	 const t_vector	p = rt->eye.pos + d * ray->dir;
	 const t_vector	v1 = rt->m[1] * (FOCAL_LENGTH / rt->config.aperture);
	 const t_vector	v2 = rt->m[2] * (FOCAL_LENGTH / rt->config.aperture);
	 ray->pos += r1 * v1 + r2 * v2;
	 ray->dir = normalize(p - ray->pos);
}

static t_color	ft_depth_of_field(__global t_rt *rt, __constant double *rand, const int2 size, const double2 coords)
{
	int			i = -1;
	t_ray		ray;
	t_color		color;
	t_color		final_color = (t_color){0, 0, 0, 0};
	t_object	obj;

	while (++i < rt->config.dof_int)
	{
		bzero(&ray, sizeof(t_ray));
		color = (t_color){0, 0, 0, 0};
		ray = ft_init_ray(rt, coords, size);
		ft_random_ray(&ray, rt, rand, i + coords.x + coords.y, coords);
		ft_check_collisions(rt, &ray);
		obj = rt->objects[ray.id];
		if (rt->config.effects && (rt->objects[ray.id].reflect || rt->objects[ray.id].transp) && ray.id != -1)
			color = ft_reflection(rt, &ray, rand);
		else if (ray.id != -1)
			color = ft_color(rt, ray, ft_light(rt, &ray, rand), rand);
		else
			color = (t_color){0, 0, 0, 0};
		final_color.r += color.r;
		final_color.g += color.g;
		final_color.b += color.b;
	}
	final_color.r /= i;
	final_color.g /= i;
	final_color.b /= i;
	final_color.c = 0xff << 24 | final_color.b << 16 | final_color.g << 8 | final_color.r;
	return (final_color);
}
