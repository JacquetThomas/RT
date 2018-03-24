/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normale.cl                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:50:13 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/02/26 16:15:18 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static t_vector		ft_check_norm(t_vector n, __global t_rt *rt, __global t_object *o)
{
	if ((rt->eye.pos.y > o->pos.y && o->rot.y < 0) || \
									(rt->eye.pos.y < o->pos.y && o->rot.y > 0))
		n.y *= -1;
	if ((rt->eye.pos.x < o->pos.x && o->rot.x > 0) || \
									(rt->eye.pos.x > o->pos.x && o->rot.x < 0))
		n.x *= -1;
	if ((rt->eye.pos.z > o->pos.z && o->rot.z < 0) || \
									(rt->eye.pos.z < o->pos.z && o->rot.z > 0))
		n.z *= -1;
	return (n);
}

static t_vector		ft_bump_mapping(__global t_object *obj, t_vector n, const t_vector hit)
{
	const t_vector		bump = {
		ft_perlin_noise(hit * .3), \
		ft_perlin_noise((t_vector){hit.y * .3, hit.x * .3, hit.x * .3}), \
		ft_perlin_noise((t_vector){hit.z * .3, hit.x * .3, hit.y * .3})
	};
	const t_vector		n2 = {
		(1.0 - obj->bm) * n.x + bump.x * n.x, \
		(1.0 - obj->bm) * n.y + bump.y * n.y, \
		(1.0 - obj->bm) * n.z + bump.z * n.z
	};

	if (dot(n2, n2) == 0.0)
		return (n);
	return (n2 * rsqrt(dot(n2, n2)));
}

static void			ft_perturbation(__global t_rt *rt, t_vector *n, __global t_object *obj, const t_vector hit)
{
	if (obj->np > 0 && rt->config.effects == 1)
	{
		n->x += sin(n->x * obj->np) * n->x / 10.0;
		n->y += sin(n->y * obj->np) * n->y / 10.0;
		n->z += sin(n->z * obj->np) * n->z / 10.0;
	}
	else if (obj->bm != 0 && rt->config.effects)
		*n = ft_bump_mapping(obj, *n, hit);
}

static t_vector		ft_normale(__global t_rt *rt, __global t_object *obj, \
								const t_vector hit, const t_ray *ray, __constant double *rand)
{
	t_vector	v1;

	if (obj->type == PLANE)
		v1 = ft_check_norm(obj->rot, rt, obj);
	else if (obj->type == SPHERE)
		v1 = hit - obj->pos;
	else
	{
		v1 = obj->rot * (dot(ray->dir, obj->rot) * ray->dist + \
											dot(ray->pos - obj->pos, obj->rot));
		if (obj->type == CONE)
			v1 = v1 * (1.0 + pow(tan(obj->size.x / 180.0 / PI) , 2.0));
		v1 = (hit - obj->pos) - v1;
	}
	ft_perturbation(rt, &v1, obj, hit);
	return (normalize(v1));
}