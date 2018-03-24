/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparency.cl                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:31:26 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/01/29 16:15:43 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static t_color		ft_transp_color(__global t_rt *rt, t_ray *ray, __constant double *rand)
{
	const int		id = ray->id;

	ray->pos = ray->pos + ray->dir * ray->dist;
	ft_check_collisions(rt, ray);
	if (id == ray->id)
	{
		ray->id = -1;
		ray->t = 200000.0;
		ray->dist = ray->t;
		ft_check_collisions(rt, ray);
	}
	if (ray->id != id && ray->id < rt->nb_obj && ray->id > -1)
		return (ft_color(rt, *ray, 1.0, rand));
	else if (ray->id == -1)
		return ((t_color){0, 0, 0, 0});
	return ((t_color){0xff, 0xff, 0xff, 0xffffffff});
}

static t_color		ft_transparency(__global t_rt *rt, const double transp, \
											t_ray *ray, __constant double *rand)
{
	t_color			c;
	const t_color	c2 = {
		rt->objects[ray->id].color.c & 0xff, \
		rt->objects[ray->id].color.c >> 8 & 0xff, \
		rt->objects[ray->id].color.c >> 16 & 0xff, \
		rt->objects[ray->id].color.c
	};
	t_color			c3;
	const double	l = min(max(ft_light(rt, ray, rand), (1.0 - transp)), 2.0);

	c = ft_transp_color(rt, ray, rand);
	c3.r = min(max((c.r * transp) + (c2.r * (1.0 - transp) * l), 0.0), 255.0);
	c3.g = min(max((c.g * transp) + (c2.g * (1.0 - transp) * l), 0.0), 255.0);
	c3.b = min(max((c.b * transp) + (c2.b * (1.0 - transp) * l), 0.0), 255.0);
	c3.c = 0xff << 24 | c.b << 16 | c.g << 8 | c.r;
	return (c3);
}