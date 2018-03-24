/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.cl                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 19:43:00 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/02/26 16:27:33 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"
#include "negative.cl"
#include "sphere.cl"
#include "plane.cl"
#include "cone.cl"
#include "cylinder.cl"
#include "cube.cl"

static void		ft_check_collisions_2(__global t_rt *rt, __global t_light *l, t_ray *ray)
{
	int			i = -1;
	t_object	o;

	while (++i < rt->nb_light)
	{
		o.size.x = 0.3;
		o.pos = l[i].pos;
		ft_sphere_col(o, ray);
		if (ray->t < ray->dist)
		{
			ray->id = i + rt->nb_obj;
			ray->dist = ray->t;
		}
	}
}

static void		ft_check_collisions(__global t_rt *rt, t_ray *ray)
{
	int			i = -1;
	t_vector	coldir = ray->coldir;
	t_vector	colpos = ray->colpos;
	int			coltype = ray->coltype;

	while (++i < rt->nb_obj)
	{
		if (rt->objects[i].type == SPHERE)
			ft_sphere_col(rt->objects[i], ray);
		else if (rt->objects[i].type == PLANE)
			ft_plane_col(rt->objects[i], ray);
		else if (rt->objects[i].type == CONE)
			ft_cone_col(rt->objects[i], ray);
		else if (rt->objects[i].type == CYLINDER)
			ft_cyl_col(rt->objects[i], ray);
		else if (rt->objects[i].type == CUBE)
			ft_cube_col(rt->objects[i], ray);
		else if (rt->objects[i].type == FOCUS && rt->config.show_focus)
			ft_plane_col(rt->objects[i], ray);
		if (ray->t < ray->dist)
		{
			ray->id = i;
			ray->dist = ray->t;
			coldir = ray->coldir;
			colpos = ray->colpos;
			coltype = ray->coltype;
		}
	}
	ray->coldir = coldir;
	ray->colpos = colpos;
	ray->coltype = coltype;
	if (ray->id != -1 && rt->objects[ray->id].negative)
		check_col_neg(rt, ray, ray->id);
	if (rt->lights && rt->config.lights)
		ft_check_collisions_2(rt, rt->lights, ray);
}
