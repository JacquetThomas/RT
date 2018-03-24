/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.cl                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:40:30 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/09 17:27:23 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"
#include "transparency.cl"

static void		ft_reflect_ray(__global t_rt *rt, t_ray *ray, __constant double *rand)
{
	t_vector	hit = ray->pos + ray->dir * ray->dist;
	t_vector	n = ft_normale(rt, &rt->objects[ray->id], hit, ray, rand);
	t_vector	r = ray->dir - (n * dot(n, ray->dir) * 2.0);

	ray->t = 200000.0;
	ray->dist = ray->t;
	ray->dir = r;
	ray->pos = hit;
	ray->id = -1;
	ray->bounces--;
}

static t_color	ft_ref_color(__global t_rt *rt, t_ray *ray, const double ref, __constant double *rand)
{
	t_color			c;
	const int		id = ray->id;

	ft_reflect_ray(rt, ray, rand);
	ft_check_collisions(rt, ray);
	if (ray->id != id && ray->id < rt->nb_obj && rt->objects[ray->id].transp && (rt->config.effects || rt->config.show_focus))
		c = ft_transparency(rt, rt->objects[ray->id].transp / 100.0, ray, rand);
	else if (ray->id != id && ray->id < rt->nb_obj)
		c = ft_color(rt, *ray, ref, rand);
	else
		c = (t_color){255, 255, 255, 0xff << 24 | 255 << 16 | 255 << 8 | 255};
	return (c);
}

static t_color	ft_reflection(__global t_rt *rt, t_ray *ray, __constant double *rand)
{
	double			light = 0.0;
	double			ref = (rt->objects[ray->id].reflect > 0.0) ? rt->objects[ray->id].reflect : 100.0;
	double			reflection = ref;
	t_color			c_ref;
	t_color			c_obj;
	const double	l2 = min(max(ft_light(rt, ray, rand), 0.0), 2.0) * (100.0 - ref) / 100.0;
	
	c_obj = ft_color(rt, *ray, 1.0, rand);
	while ((((rt->objects[ray->id].reflect && ray->bounces) || rt->objects[ray->id].transp)) && reflection > 1.0)
	{
		if (rt->objects[ray->id].reflect && !rt->config.show_focus)
		{
			c_ref = ft_ref_color(rt, ray, reflection / 100.0, rand);
			ref = (rt->objects[ray->id].reflect > 0) ? \
											rt->objects[ray->id].reflect : 100;
			reflection *= (ref / 100.0);
		}
		if (rt->objects[ray->id].transp)
			c_ref = ft_transparency(rt, rt->objects[ray->id].transp / 100.0, ray, rand);
	}
	light += ft_light(rt, ray, rand);
	c_ref.r = min(max(((min(max((c_ref.r * light) + min(max(255.0 * (light - 1.0), \
			0.0), 255.0), 0.0), 255.0) * reflection / 100.0) + (c_obj.r * l2 * \
			((100.0 - reflection) / 100.0))), 0.0), 255.0);
	c_ref.g = min(max(((min(max((c_ref.g * light) + min(max(255.0 * (light - 1.0), \
			0.0), 255.0), 0.0), 255.0) * reflection / 100.0) + (c_obj.g * l2 * \
			((100.0 - reflection) / 100.0))), 0.0), 255.0);
	c_ref.b = min(max(((min(max((c_ref.b * light) + min(max(255.0 * (light - 1.0), \
			0.0), 255.0), 0.0), 255.0) * reflection / 100.0) + (c_obj.b * l2 * \
			((100.0 - reflection) / 100.0))), 0.0), 255.0);
	c_ref.c = 0xff << 24 | c_ref.b << 16 | c_ref.g << 8 | c_ref.r;
	return (c_ref);
}

static t_color	ft_focus_plane(__global t_rt *rt, t_ray *ray, __constant double *rand)
{
	double			light = 0.0;
	double			ref = (rt->objects[ray->id].reflect > 0.0) ? rt->objects[ray->id].reflect : 100.0;
	double			reflection = ref;
	t_color			c_ref;
	t_color			c_obj;
	const double	l2 = min(max(ft_light(rt, ray, rand), 0.0), 2.0) * (100.0 - ref) / 100.0;
	
	c_obj = ft_color(rt, *ray, 1.0, rand);
	while (rt->config.dof && rt->config.show_focus && rt->objects[ray->id].type == FOCUS)
		if (rt->objects[ray->id].type == FOCUS)
			c_ref = ft_transparency(rt, rt->objects[ray->id].transp / 100.0, ray, rand);
	light += ft_light(rt, ray, rand);
	c_ref.r = min(max(((min(max((c_ref.r * light) + min(max(255.0 * (light - 1.0), \
			0.0), 255.0), 0.0), 255.0) * reflection / 100.0) + (c_obj.r * l2 * \
			((100.0 - reflection) / 100.0))), 0.0), 255.0);
	c_ref.g = min(max(((min(max((c_ref.g * light) + min(max(255.0 * (light - 1.0), \
			0.0), 255.0), 0.0), 255.0) * reflection / 100.0) + (c_obj.g * l2 * \
			((100.0 - reflection) / 100.0))), 0.0), 255.0);
	c_ref.b = min(max(((min(max((c_ref.b * light) + min(max(255.0 * (light - 1.0), \
			0.0), 255.0), 0.0), 255.0) * reflection / 100.0) + (c_obj.b * l2 * \
			((100.0 - reflection) / 100.0))), 0.0), 255.0);
	c_ref.c = 0xff << 24 | c_ref.b << 16 | c_ref.g << 8 | c_ref.r;
	return (c_ref);
}