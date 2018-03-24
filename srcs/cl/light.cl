/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 14:27:12 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/02/26 16:21:08 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"
#include "normale.cl"
#include "shadows.cl"

static double	ft_calc_light(__global t_rt *rt, __global t_object *obj, \
				__global t_light *l, const t_ray *ray, __constant double *rand)
{
	const t_vector	a = ray->pos + (ray->dir * ray->t);
	const t_vector	v = normalize(l->pos - a);
	const t_vector	b = ft_normale(rt, obj, a, ray, rand);
	const t_vector	c = normalize(v - rt->m[0]);
	double			light = min(max(dot(v, b) * (l->intensity / 100.0), 0.0), 1.3);
	const double	tmp = pow(dot(b, c), 50.0) * dot(b, v) * (l->intensity / 100.0);

	if (tmp > 0.0000001 && obj->type != PLANE)
		light += tmp;
	if (rt->config.effects && rt->config.shadows == 0)
		light *= 1.0 - ft_hard_shadows(rt, a, l);
	else if (rt->config.effects && rt->config.shadows == 1)
		light *= 1.0 - ft_soft_shadows(rt, a, l, rand);
	return (min(max(light, 0.0), 1.3));
}

static double	ft_light(__global t_rt *rt, const t_ray *ray, __constant double *rand)
{
	int		i = -1;
	double	light = 0.0;

	if (ray->id < rt->nb_obj)
		while (++i < rt->nb_light)
			light += ft_calc_light(rt, &rt->objects[ray->id], &rt->lights[i], ray, rand);
	else
		light = rt->lights[ray->id - rt->nb_obj].intensity / 100.0;
	return (min(max(light, rt->config.ambient), 1.0 + rt->objects[ray->id].spec));
}