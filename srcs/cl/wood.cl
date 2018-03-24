/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wood.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 18:21:10 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/01 14:17:49 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static t_color		ft_wood(const t_vector hit, const __global t_object *obj)
{
	const double	noise = ft_perlin_noise(hit * obj->noise.freq) * 2.0;
	const double	a = 16 * fabs(sin(2.0 * hit.x + ((length(hit) + obj->noise.freq) * noise / 256.0) * PI));
	const t_color	c = {
		.b = (int)(a + 35), \
		.g = (int)(a + 50), \
		.r = (int)(a + 72), \
		.c = 0xff << 24 | c.b << 16 | c.g << 8 | c.r
	};
	return (c);
}