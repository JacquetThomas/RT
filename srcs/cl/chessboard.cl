/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chessboard.cl                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 18:19:11 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/12/05 14:52:48 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static double2		ft_get_chess_size(const int type, const __global t_object *obj)
{
	if (type == SPHERE)
		return ((double2){CHESS_SIZE * 1500, CHESS_SIZE * 3000});
	else if (type == CYLINDER)
		return ((double2){(CHESS_SIZE * 100 * (obj->size.x / 2.0)), CHESS_SIZE * 50});
	else
		return ((double2){CHESS_SIZE, CHESS_SIZE});
}

static t_color		ft_chessboard(const double2 hit, const __global t_object *obj, const t_vector n)
{
	const double2	size = ft_get_chess_size(obj->type, obj);
	
	if (fmod((floor(hit.x * size.x) + floor(hit.y * size.y)), 2.0) == 0)
		return ((t_color){0, 0, 0, 0});
	return ((t_color){0xff, 0xff, 0xff, 0xffffffff});
}