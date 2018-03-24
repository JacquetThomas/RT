/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 14:38:00 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/17 16:52:19 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static void		ft_putpixel(t_win *win, int y, int x, int color)
{
	int		i;

	i = 0;
	if (x < WIN_W && y < WIN_H && x >= 0 && y >= 0)
	{
		i = win->linelen * y + x * (win->bpp / 8);
		win->data[i] = color & 0xff;
		win->data[++i] = color >> 8 & 0xff;
		win->data[++i] = color >> 16 & 0xff;
	}
}

static int		ft_texture(t_rt *rt)
{
	t_vector	hit;

	hit = rt->eye.pos + rt->ray.dir * rt->ray.t;
	if (hit.x > 0 && hit.z > 0)
	{
		if ((fmod(hit.x+ 1000.0, 50.0) > 25.0 && fmod(hit.z + 1000.0, 50.0) > 25.0) || \
			(fmod(hit.x+ 1000.0, 50.0) < 25.0 && fmod(hit.z + 1000.0, 50.0) < 25.0))
			return (0);
		return (255 << 16 | 255 << 8 | 255);
	}
	return (255 << 16 | 255 << 8 | 255);
}

static int		ft_get_obj_color(t_rt *rt, double l)
{
	int		color;
	int		red;
	int		blue;
	int		green;
	int		i;

	color = 0;
	i = rt->ray.id;
	if (i < 0)
		return (0);
	if (i >= rt->nb_obj)
		return ((int)(255 * max(l, 1.0)) << 16 | (int)(255 * max(l, 1.0)) << 8 | (int)(255 * max(l, 1.0)));
	rt->ray.bounces = MAX_BOUNCES;
	if (rt->objects[i].reflect > 0)
		color = ft_reflection(rt);
	else
		color = rt->objects[i].color;
	l = min(max(l, 0.0), 2.0);
	blue = min(max(min(max(((color & 0xff) * (l * BL)), 0.0, 255.0) + min(max(220.0 * (l - 1.0), 0.0, 255.0), 0.0, 255.0));
	green = min(max(min(max(((color >> 8 & 0xff) * (l * GL)), 0.0, 255.0) + min(max(244.0 * (l - 1.0), 0.0, 255.0), 0.0, 255.0));
	red = min(max(min(max(((color >> 16 & 0xff) * (l * RL)), 0.0, 255.0) + min(max(255.0 * (l - 1.0), 0.0, 255.0), 0.0, 255.0));
	return (red << 16 | green << 8 | blue);
}
