/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bricks.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 18:19:02 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/02/26 18:09:07 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static double2		ft_brick_size(__global const t_object *obj, int i)
{
	if (i == 0)
	{
		if (obj->type == SPHERE)
			return ((double2){BRICK_W, BRICK_H});
		else if (obj->type == CYLINDER)
			return ((double2){BRICK_W * 1.95, BRICK_H * 40.0 / 1.5});
		else if (obj->type == PLANE)
			return ((double2){BRICK_H * 300.0, BRICK_W * 200.0});
	}
	else
	{
		if (obj->type == SPHERE)
			return ((double2){MORTAR_W, MORTAR_H});
		else if (obj->type == CYLINDER)
			return ((double2){MORTAR_W, MORTAR_H * 20.0});
		else if (obj->type == PLANE)
			return ((double2){MORTAR_W * 250.0, MORTAR_H * 400.0});
	}
	return (((double2){0, 0}));
}

static t_color		ft_bricks(double2 coords, __constant double *rand, __global const t_object *obj)
{
	const double2	b_size = ft_brick_size(obj, 0);
	const double2	m_size = ft_brick_size(obj, 1);
	const double2	c = {
		((obj->type == PLANE) ? fabs(coords.x) : coords.x), \
		((obj->type == PLANE) ? (int)fabs(coords.y) : coords.y)
	};
	const double	v = ((coords.y < 0.0) ? ceil(c.y / (b_size.y + (2.0 * m_size.y))) : floor(c.y / (b_size.y + (2.0 * m_size.y))));
	const double	u = (fabs(fmod(v, 2.0)) > 0.0001) ? c.x + (b_size.x / 2.0) + m_size.x : c.x;
	const double	v2 = fmod(c.y, (b_size.y + 2.0 * m_size.y));
	const double	u2 = fmod(u, (b_size.x + 2.0 * m_size.x));
	const int		brick = ((v2 > m_size.y && v2 < (m_size.y + b_size.y)) && (u2 > m_size.x && u2 < (b_size.x + m_size.x)));
	const double	r = fmod(fabs(*rand) * 1510068.5236, 100.0);
	
	if (brick && (r >= 0 && r < 40))
		return ((t_color){0xa8, 0x47, 0x46, 0xff4647a8});
	else if (brick && (r >= 40 && r < 50))
		return ((t_color){0x71, 0x2a, 0x29, 0xff292a71});
	else if (brick && (r >= 50 && r < 60))
		return ((t_color){0xaf, 0x51, 0x42, 0xff4251af});
	else if (brick && (r >= 60 && r < 80))
		return ((t_color){0xc3, 0x71, 0x61, 0xff6171c3});
	else if (brick && (r >= 80 && r < 85))
		return ((t_color){0xd7, 0x93, 0x80, 0xff8093d7});
	else if (brick && (r >= 85 && r < 93))
		return ((t_color){0xeb, 0x75, 0x47, 0xff4775eb});
	else if (brick && (r >= 93 && r < 100))
		return ((t_color){0xa9, 0x54, 0x38, 0xff3854a9});
	else if (!brick && (r >= 0 && r < 40))
		return ((t_color){0xdd, 0xcf, 0xcf, 0xffcfcfdd});
	else if (!brick && (r >= 40 && r < 55))
		return ((t_color){0xe2, 0xd6, 0xd9, 0xffd9d6e2});
	else if (!brick && (r >= 55 && r < 65))
		return ((t_color){0xe2, 0xce, 0xce, 0xffcecee2});
	else if (!brick && (r >= 65 && r < 80))
		return ((t_color){0xda, 0xcb, 0xcf, 0xffcfcbda});
	else if (!brick && (r >= 80 && r < 95))
		return ((t_color){0xd8, 0xbc, 0xb9, 0xffb9bcd8});
	else
		return ((t_color){0xa0, 0xa0, 0xa0, 0xffa0a0a0});
}