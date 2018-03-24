/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:12:20 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/17 18:48:50 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static void		ft_plane_col(const t_object obj, t_ray *ray)
{
	const double	d = (dot(obj.rot, obj.pos) - dot(obj.rot, ray->pos)) \
												/ dot(obj.rot, ray->dir) - (obj.negative ? 0 : .1);
	const t_vector	pos_hit = (ray->dir * d + ray->pos) - obj.pos;

	if (d > 0.0000001 && d < ray->t)
	{
		if (obj.size.x && obj.size.y)
		{
			if (obj.size.x / 2 <= fabs(dot(pos_hit, \
				normalize((t_vector){(obj.rot.y * obj.rot.y / (obj.rot.z + 0.000000001)) + obj.rot.z, \
				-obj.rot.x * obj.rot.y / (obj.rot.z + 0.000000001), -obj.rot.x}))) || \
				obj.size.y / 2 <= fabs(dot(pos_hit, \
				normalize((t_vector){0, -1, obj.rot.y / (obj.rot.z + 0.000000001)}))))
				return ;
		}
		else if (obj.size.x)
		{
			if (obj.size.x / 2 <= fabs(length(pos_hit)))
				return ;
		}
		ray->coltype = PLANE;
		ray->colpos = obj.pos;
		ray->coldir = obj.rot;
		ray->otherside = d;
		ray->t = d;
	}
}

static double2		ft_plane_text_coords(const t_vector hit, const __global t_object *obj)
{
	const t_vector	v1 = {obj->pos.x - 0.0000000000001, obj->pos.y, obj->pos.z};
	const t_vector	v2 = cross(v1, obj->rot);
	double2			c = {
		dot(hit, v1), \
		dot(hit, v2)
	};

	c.x -= (c.x < 0.0) ? 1.0 : 0.0;
	c.x += (c.x > 1.0) ? 1.0 : 0.0;
	c.y -= (c.y < 0.0) ? 1.0 : 0.0;
	c.y += (c.y > 1.0) ? 1.0 : 0.0;
	return (c);
}
