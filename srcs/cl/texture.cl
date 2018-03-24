/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.cl                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 15:46:09 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/02/26 17:35:12 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"
#include "chessboard.cl"
#include "bricks.cl"
#include "wood.cl"
#include "marble.cl"
#include "noise.cl"

static double2		ft_get_text_coords(const t_vector hit, __global \
			t_object *obj, const t_ray *ray, __constant double *rand, __global t_rt *rt)
{
	if (obj->type == SPHERE)
		return (ft_sphere_text_coords(hit, obj));
	else if (obj->type == PLANE)
		return (ft_plane_text_coords(hit, obj));
	else
		return (ft_cyl_text_coords(hit, obj, ray, rand));
}

static double		ft_lerp(double d, t_vector v)
{
	const double	c1 = -1.0;
	const double	c2 = -0.5;
	const double	c3 = 0.5;
	const double	c4 = 1.0;

	if (d >= c1 && d < c2)
		return (((v.x * (d - c1)) / (c2 - c1)) + ((v.y * (c2 - d)) / (c2 - c1)));
	else if (d >= c2 && d < c3)
		return (((v.y * (d - c2)) / (c3 - c2)) + ((v.x * (c3 - d)) / (c3 - c2)));
	return (((v.x * (d - c3)) / (c4 - c3)) + ((v.z * (c4 - d)) / (c4 - c3)));
}

static t_color		ft_procedural_texture(__global t_rt *rt, t_ray ray, \
								__global t_object *obj, __constant double *rand)
{
	const t_vector	hit = ray.pos + ((ray.dist - .1) * ray.dir);

	if (obj->p_texture == CHESSBOARD)
		return (ft_chessboard(ft_get_text_coords(hit, obj, &ray, rand, rt), obj, ft_normale(rt, obj, hit, &ray, rand)));
	else if (obj->p_texture == WOOD)
		return (ft_wood(hit, obj));
	else if (obj->p_texture == MARBLE)
		return (ft_marble(hit, obj));
	else if (obj->p_texture == BRICKS)
		return (ft_bricks(ft_get_text_coords(hit, obj, &ray, rand, rt), &rand[(int)fmod(fabs(((hit.x * 10000000.0) + (hit.y * 10000000.0) + (hit.z * 10000000.0))), MAX_RAND) - 1], obj));
	return ((t_color){0, 0, 0, 0});
}
