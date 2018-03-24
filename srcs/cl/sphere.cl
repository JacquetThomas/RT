/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:12:34 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/13 20:03:51 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static void			ft_sphere_col(const t_object obj, t_ray *ray)
{
	const t_vector		dist = ray->pos - obj.pos;
	t_equation			e = {
		.a = dot(ray->dir, ray->dir), \
		.b = 2 * dot(ray->dir, dist), \
		.c = dot(dist, dist) - (obj.size.x * obj.size.x), \
		.delta = e.b * e.b - 4.0 * e.a * e.c
	};

	if (e.delta < 0.0)
		return ;
	e.c = (0 < e.c) ? (-e.b + sqrt(e.delta)) / (2.0 * e.a) : ray->t;
	e.delta = (0 < e.delta) ? (-e.b - sqrt(e.delta)) / (2.0 * e.a) : ray->t;
	if (e.c > e.delta)
	{
		e.a = e.c;
		e.c = e.delta;
		e.delta = e.a;
	}
	ray->otherside = (e.delta != ray->t) ? e.delta : e.c;
	if (e.c > 0.0000001 && e.c < ray->t)
	{
		ray->coldir = obj.rot;
		ray->colpos = obj.pos;
		ray->coltype = SPHERE;
		ray->t = e.c;
	}
}

static double2		ft_sphere_text_coords(const t_vector hit, const __global t_object *obj)
{
	const t_vector	n = normalize(hit - obj->pos);
	double2			c = {
		(obj->size.x) + atan2(n.y, n.x) / M_PI_2,	\
		(obj->size.x) - asin(n.z) / M_PI
	};
	
	c.x -= (c.x < 0.0) ? 1.0 : 0.0;
	c.x += (c.x > 1.0) ? 1.0 : 0.0;
	c.y -= (c.y < 0.0) ? 1.0 : 0.0;
	c.y += (c.y > 1.0) ? 1.0 : 0.0;
	return (c);
}