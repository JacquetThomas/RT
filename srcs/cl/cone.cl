/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:12:25 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/02/26 17:34:47 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static void			ft_cone_col(const t_object obj, t_ray *ray)
{
	const t_vector		dist = ray->pos - obj.pos;
	const t_vector		rot = obj.rot;
	t_ray				tmpray = *ray;
	int					nbcol = 0;
	t_equation			e = {
		.a = dot(ray->dir, ray->dir) - (1.0 + pow(tan(PI * (obj.size.x / 180.0)), 2.0)) * pow(dot(ray->dir, rot), 2.0), \
		.b = 2 * (dot(ray->dir, dist) - (1.0 + pow(tan(PI * (obj.size.x / 180.0)), 2.0)) * dot(ray->dir, rot) * dot(dist, rot)), \
		.c = dot(dist, dist) - (1.0 + pow(tan(PI * (obj.size.x / 180.0)), 2.0)) * pow(dot(dist, rot), 2.0), \
		.delta = e.b * e.b - 4.0 * e.a * e.c
	};

	if (e.delta < 0.0 && !dot(ray->dir, obj.rot))
		return ;
	if (0.0 <= e.delta)
	{
		e.c = 0 < (-e.b + sqrt(e.delta)) / (2 * e.a) ? (-e.b + sqrt(e.delta)) / (2 * e.a) : ray->t;
		e.delta = 0 < (-e.b - sqrt(e.delta)) / (2 * e.a) ? (-e.b - sqrt(e.delta)) / (2 * e.a) : ray->t;
		if ((obj.size.y && obj.size.y / 2 < length(ray->pos + ray->dir * e.c - obj.pos) * cos(obj.size.x * M_PI / 180)) || (obj.size.z == 1 && dot(ray->pos + ray->dir * e.c - obj.pos, obj.rot) < 0))
			e.c = ray->t;
		if ((obj.size.y && obj.size.y / 2 < length(ray->pos + ray->dir * e.delta - obj.pos) * cos(obj.size.x * M_PI / 180)) || (obj.size.z == 1 && dot(ray->pos + ray->dir * e.delta - obj.pos, obj.rot) < 0))
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
		++nbcol;
		ray->coldir = obj.rot;
		ray->colpos = obj.pos;
		ray->coltype = obj.type;
	}
	if (e.delta != ray->t)
		++nbcol;
	if (obj.size.y && !obj.size.z)
	{
		if (dot(ray->dir, obj.rot))
		{
			ft_plane_col((const t_object){obj.pos + obj.rot * obj.size.y / 2, obj.rot, (t_vector){obj.size.y * tan(obj.size.x * M_PI / 180), 0, 0}, .negative = obj.negative}, &tmpray);
			if (0 < tmpray.t && tmpray.t < ray->t)
			{
				if (tmpray.t < e.delta)
					e.delta = tmpray.t;
				if (e.delta < e.c)
				{
					++nbcol;
					e.b = e.c;
					e.c = e.delta;
					e.delta = e.b;
					ray->coldir = tmpray.coldir;
					ray->colpos = tmpray.colpos;
					ray->coltype = tmpray.coltype;
				}
			}
			tmpray.t = ray->t;
			ft_plane_col((const t_object){obj.pos - obj.rot * obj.size.y / 2, obj.rot, (t_vector){obj.size.y * tan(obj.size.x * M_PI / 180), 0, 0}, .negative = obj.negative}, &tmpray);
			if (0 < tmpray.t && tmpray.t < ray->t)
			{
				if (tmpray.t < e.delta)
					e.delta = tmpray.t;
				if (e.delta < e.c)
				{
					++nbcol;
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
	else if (obj.size.y && obj.size.z)
	{
		if (dot(ray->dir, obj.rot))
		{
			ft_plane_col((const t_object){obj.pos + obj.rot * obj.size.y / 2, obj.rot, (t_vector){obj.size.y * tan(obj.size.x * M_PI / 180), 0, 0}, .negative = obj.negative}, &tmpray);
			if (0 < tmpray.t)
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
	ray->otherside = (e.delta != ray->t && nbcol % 2 == 0) ? e.delta : e.c;
	if (e.c > 0.0000001 && e.c < ray->t)
		ray->t = e.c;
}
