/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:54:15 by cjacquet          #+#    #+#             */
/*   Updated: 2018/03/17 17:50:01 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		on_button_aa(int x, int y, t_rt *rt)
{
	if (x >= ((WIN_W - IM_W) + 20) && x <= ((WIN_W - IM_W) + 20 + BUTTON_W) && \
			y >= (15 * SEP_H) && y <= (16 * SEP_H - 2))
		return (1);
	if (x >= ((WIN_W - IM_W) + 20 + BUTTON_W + 10) && \
			x <= ((WIN_W - IM_W) + 20 + BUTTON_W + 10 + BUTTON_W) && \
			y >= (15 * SEP_H) && y <= (16 * SEP_H - 2))
		return (4);
	if (x >= ((WIN_W - IM_W) + 20 + 2 * BUTTON_W + 2 * 10) && \
			x <= ((WIN_W - IM_W) + 20 + 3 * BUTTON_W + 20) && \
			y >= (15 * SEP_H) && y <= (16 * SEP_H - 2))
		return (8);
	if (x >= ((WIN_W - IM_W) + 20) && x <= ((WIN_W - IM_W) + 20 + BUTTON_W) && \
			y >= (16 * SEP_H) && y <= (17 * SEP_H - 2))
		return (12);
	if (x >= ((WIN_W - IM_W) + 20 + BUTTON_W + 10) && \
			x <= ((WIN_W - IM_W) + 20 + 10 + 2 * BUTTON_W) && \
			y >= (16 * SEP_H) && y <= (17 * SEP_H - 2))
		return (16);
	if (x >= ((WIN_W - IM_W) + 20 + 2 * BUTTON_W + 20) && \
			x <= ((WIN_W - IM_W) + 20 + 3 * BUTTON_W + 20) && \
			y >= (16 * SEP_H) && y <= (17 * SEP_H - 2))
		return (20);
	return (rt->config.aa);
}

void	call_filters(int fil, SDL_Surface *eff, SDL_Surface *draw)
{
	static void	(*ft[3])(uint32_t*) = {ft_cartoon, ft_sepia, ft_bw};

	if (SDL_BlitSurface(draw, NULL, eff, NULL))
		errors(ERR_SDL, "SDL_BlitSurface call_filters failed --");
	ft[fil - 1](eff->pixels);
}

int		on_button_filter(int x, int y, t_sdl *sdl)
{
	if (y >= (19 * SEP_H) && y <= (20 * SEP_H - 2))
	{
		if (x >= ((WIN_W - IM_W) + 20) && \
				x <= ((WIN_W - IM_W) + 20 + BUTTON_W))
		{
			sdl->filters = sdl->filters ? 0 : CARTOON;
			return (1);
		}
		if (x >= ((WIN_W - IM_W) + 30 + BUTTON_W) && \
				x <= ((WIN_W - IM_W) + 30 + BUTTON_W * 2))
		{
			sdl->filters = sdl->filters ? 0 : SEPIA;
			return (1);
		}
		if (x >= ((WIN_W - IM_W) + 40 + 2 * BUTTON_W) && \
				x <= ((WIN_W - IM_W) + 40 + 3 * BUTTON_W))
		{
			sdl->filters = sdl->filters ? 0 : BW;
			return (1);
		}
	}
	return (0);
}
