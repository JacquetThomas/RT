/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.cl                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:12:23 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/17 18:47:37 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static void			ft_cyl_col(const t_object obj, t_ray *ray)
{
	const t_vector		dist = ray->pos - obj.pos;
	const t_vector		rot = obj.rot;
	t_ray				tmpray = *ray;
	t_equation			e = {
		.a = dot(ray->dir, ray->dir) - pow(dot(ray->dir, rot), 2.0), \
		.b = 2 * (dot(ray->dir, dist) - dot(ray->dir, rot) * dot(dist, rot)), \
		.c = dot(dist, dist) - pow(dot(dist, rot), 2) - pow(obj.size.x, 2), \
		.delta = e.b * e.b - 4.0 * e.a * e.c
	};

	if (0.0 <= e.delta)
	{
		e.c = 0 < (-e.b + sqrt(e.delta)) / (2 * e.a) ? (-e.b + sqrt(e.delta)) / (2 * e.a) : ray->t;
		e.delta = 0 < (-e.b - sqrt(e.delta)) / (2 * e.a) ? (-e.b - sqrt(e.delta)) / (2 * e.a) : ray->t;
		if (obj.size.y && obj.size.y / 2 < sqrt(pow(length(e.c * ray->dir + ray->pos - obj.pos), 2) - pow(obj.size.x, 2)))
			e.c = ray->t;
		if (obj.size.y && obj.size.y / 2 < sqrt(pow(length(e.delta * ray->dir + ray->pos - obj.pos), 2) - pow(obj.size.x, 2)))
			e.delta = ray->t;
		if (e.delta < e.c)
		{
			e.b = e.c;
			e.c = e.delta;
			e.delta = e.b;
		}
	}
	else
	{
		e.c = ray->t;
		e.delta = ray->t;
	}
	if (e.c != ray->t)
	{
		ray->coldir = obj.rot;
		ray->colpos = obj.pos;
		ray->coltype = obj.type;
	}
	if (obj.size.y)
	{
		if (dot(ray->dir, obj.rot))
		{
			ft_plane_col((const t_object){obj.pos + obj.rot * obj.size.y / 2, obj.rot, (t_vector){obj.size.x * 2, 0, 0}, .negative = obj.negative}, &tmpray);
			if (0 < tmpray.t && tmpray.t < ray->t)
			{
				if (tmpray.t < e.delta)
					e.delta = tmpray.t;
				if (e.delta < e.c)
				{
					e.b = e.c;
					e.c = e.delta;
					e.delta = e.b;
					ray->coldir = tmpray.coldir;
					ray->colpos = tmpray.colpos;
					ray->coltype = tmpray.coltype;
				}
			}
			tmpray.t = ray->t;
			ft_plane_col((const t_object){obj.pos - obj.rot * obj.size.y / 2, obj.rot, (t_vector){obj.size.x * 2, 0, 0}, .negative = obj.negative}, &tmpray);
			if (0 < tmpray.t && tmpray.t < ray->t)
			{
				if (tmpray.t < e.delta)
					e.delta = tmpray.t;
				if (e.delta < e.c)
				{
					e.b = e.c;
					e.c = e.delta;
					e.delta = e.b;
					ray->coldir = tmpray.coldir;
					ray->colpos = tmpray.colpos;
					ray->coltype = tmpray.coltype;
				}
			}
		}
	}
	ray->otherside = (e.delta != ray->t) ? e.delta : e.c;
	if (e.c > 0.0000001 && e.c < ray->t)
		ray->t = e.c;
}
	
static double2		ft_cyl_text_coords(const t_vector hit, const __global t_object *obj, const t_ray *ray, __constant double *rand)
{
	const t_vector		n = (hit - obj->pos) - (obj->rot * (dot(ray->dir, obj->rot) * ray->dist + dot(ray->pos - obj->pos, obj->rot)));
	double2			c = {
		atan2(n.x, n.z), \
		hit.y + ((obj->p_texture == BRICKS) ? 100000 : 0)
	};
	
	c.x -= (c.x < 0.0) ? 1.0 : 0.0;
	c.x += (c.x > 1.0) ? 1.0 : 0.0;
	c.y -= (c.y < 0.0) ? 3.05 : 0.0;
	c.y += (c.y > 3.05) ? 3.05 : 0.0;
	return (fabs(c));
}
