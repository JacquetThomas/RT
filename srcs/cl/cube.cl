/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 20:49:35 by eferrand          #+#    #+#             */
/*   Updated: 2018/01/20 20:49:37 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static void			ft_cube_col(const t_object obj, t_ray *ray)
{
	double	a = ray->t;
	double	b = ray->t;
	double	c = 0.0;
	t_ray	tmpray = *ray;
	
	ft_plane_col((const t_object){.pos = obj.pos - obj.rot * obj.size.x / 2, .rot = obj.rot, .size = (t_vector){obj.size.x, obj.size.x, 0}, .negative = obj.negative}, &tmpray);
	if (0 < tmpray.t)
	{
		if (tmpray.t < b)
			b = tmpray.t;
		if (b < a)
		{
			c = a;
			a = b;
			b = c;
			ray->coldir = tmpray.coldir;
			ray->colpos = tmpray.colpos;
			ray->coltype = tmpray.coltype;
		}
	}
	tmpray.t = ray->t;
	ft_plane_col((const t_object){obj.pos + obj.rot * obj.size.x / 2, obj.rot, (t_vector){obj.size.x, obj.size.x, 0}, .negative = obj.negative}, &tmpray);
	if (0 < tmpray.t)
	{
		if (tmpray.t < b)
			b = tmpray.t;
		if (b < a)
		{
			c = a;
			a = b;
			b = c;
			ray->coldir = tmpray.coldir;
			ray->colpos = tmpray.colpos;
			ray->coltype = tmpray.coltype;
		}
	}
	tmpray.t = ray->t;
	ft_plane_col((const t_object){obj.pos - normalize((t_vector){(obj.rot.y * obj.rot.y / (obj.rot.z + 0.000000001)) + obj.rot.z, -obj.rot.x * obj.rot.y / (obj.rot.z + 0.000000001), -obj.rot.x}) * obj.size.x / 2, normalize((t_vector){(obj.rot.y * obj.rot.y / (obj.rot.z + 0.000000001)) + obj.rot.z, -obj.rot.x * obj.rot.y / (obj.rot.z + 0.000000001), -obj.rot.x}), (t_vector){obj.size.x, obj.size.x, 0}, .negative = obj.negative}, &tmpray);
	if (0 < tmpray.t)
	{
		if (tmpray.t < b)
			b = tmpray.t;
		if (b < a)
		{
			c = a;
			a = b;
			b = c;
			ray->coldir = tmpray.coldir;
			ray->colpos = tmpray.colpos;
			ray->coltype = tmpray.coltype;
		}
	}
	tmpray.t = ray->t;
	ft_plane_col((const t_object){.pos = obj.pos + normalize((t_vector){(obj.rot.y * obj.rot.y / (obj.rot.z + 0.000000001)) + obj.rot.z,-obj.rot.x * obj.rot.y / (obj.rot.z + 0.000000001),-obj.rot.x}) * obj.size.x / 2, .rot = normalize((t_vector){(obj.rot.y * obj.rot.y / (obj.rot.z + 0.000000001)) + obj.rot.z,-obj.rot.x * obj.rot.y / (obj.rot.z + 0.000000001),-obj.rot.x}), .size = (t_vector){obj.size.x, obj.size.x, 0}, .negative = obj.negative}, &tmpray);
	if (0 < tmpray.t)
	{
		if (tmpray.t < b)
			b = tmpray.t;
		if (b < a)
		{
			c = a;
			a = b;
			b = c;
			ray->coldir = tmpray.coldir;
			ray->colpos = tmpray.colpos;
			ray->coltype = tmpray.coltype;
		}
	}
	tmpray.t = ray->t;
	ft_plane_col((const t_object){obj.pos - normalize((t_vector){0, -1, obj.rot.y / (obj.rot.z + 0.000000001)}) * obj.size.x / 2, normalize((t_vector){0, -1, obj.rot.y / (obj.rot.z + 0.000000001)}), (t_vector){obj.size.x, obj.size.x, 0}, .negative = obj.negative}, &tmpray);
	if (0 < tmpray.t)
	{
		if (tmpray.t < b)
			b = tmpray.t;
		if (b < a)
		{
			c = a;
			a = b;
			b = c;
			ray->coldir = tmpray.coldir;
			ray->colpos = tmpray.colpos;
			ray->coltype = tmpray.coltype;
		}
	}
	tmpray.t = ray->t;
	ft_plane_col((const t_object){.pos = obj.pos + normalize((t_vector){0, -1, obj.rot.y / (obj.rot.z + 0.000000001)}) * obj.size.x / 2, normalize((t_vector){0, -1, obj.rot.y / (obj.rot.z + 0.000000001)}), (t_vector){obj.size.x, obj.size.x, 0}, .negative = obj.negative}, &tmpray);
	if (0 < tmpray.t)
	{
		if (tmpray.t < b)
			b = tmpray.t;
		if (b < a)
		{
			c = a;
			a = b;
			b = c;
			ray->coldir = tmpray.coldir;
			ray->colpos = tmpray.colpos;
			ray->coltype = tmpray.coltype;
		}
	}
	ray->otherside = (b != ray->t) ? b : a;
	if (a > 0.0000001 && a < ray->t)
		ray->t = a;
}
