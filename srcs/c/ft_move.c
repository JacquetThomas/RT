/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 17:37:00 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/01/08 15:16:31 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_calc_dir_vec(t_eye *eye, t_vector *m)
{
	m[0] = eye->rot;
	if (fabs(ft_norm_vector(m[0]).y) == 1)
		m[0].x = m[0].y / 10000.0 * ((m[0].y > 0) ? 1 : -1);
	m[0] = ft_norm_vector(m[0]);
	m[1] = ft_norm_vector(ft_vector_product(m[0], ft_new_vector(0, -1, 0)));
	m[2] = ft_vector_product(m[1], m[0]);
}

void	ft_rotate_y(t_eye *eye, t_vector *m, int i)
{
	t_vector	rot;

	rot = eye->rot;
	eye->rot.x = rot.x * cos(PI / 180.0 * (i * ROT_SPEED)) - rot.z * \
											sin(PI / 180.0 * (i * ROT_SPEED));
	eye->rot.z = rot.x * sin(PI / 180.0 * (i * ROT_SPEED)) + rot.z * \
											cos(PI / 180.0 * (i * ROT_SPEED));
	ft_calc_dir_vec(eye, m);
}

void	ft_rotate_z(t_eye *eye, t_vector *m, int i)
{
	t_vector	rot;

	rot = eye->rot;
	eye->rot.x = rot.x * cos(PI / 180.0 * (i * ROT_SPEED)) - rot.y * \
											sin(PI / 180.0 * (i * ROT_SPEED));
	eye->rot.y = rot.x * sin(PI / 180.0 * (i * ROT_SPEED)) + rot.y * \
											cos(PI / 180.0 * (i * ROT_SPEED));
	ft_calc_dir_vec(eye, m);
}
