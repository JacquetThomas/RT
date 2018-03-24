/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marble.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 18:28:46 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/01/30 17:17:11 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static t_color		ft_marble(const t_vector hit, const __global t_object *obj)
{
	t_noise		n2 = obj->noise;
	double		noise = 0.0;
	double		intensity = 1.2;
	int			i = -1;

	while (++i != n2.oct)
	{
		noise += (double)ft_perlin_noise(hit * n2.freq) * intensity;
		intensity *= n2.persis;
		n2.freq *= 2.0;
	}
	noise = min(ft_lerp(cos(noise * ((1.0 - n2.persis) / (1.0 - intensity))), (t_vector){0.05, 50, 70}), 1.0);

	const t_color	c = {
		.b = (int)((noise * 0.97) * 255), \
		.g = (int)((noise * 0.97) * 255), \
		.r = (int)(noise * 255), \
		.c = 0xff << 24 | c.b << 16 | c.g << 8 | c.r
	};
	return (c);
}