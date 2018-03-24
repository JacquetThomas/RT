/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_info2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 18:32:41 by cjacquet          #+#    #+#             */
/*   Updated: 2018/03/17 14:50:31 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		print_irect(SDL_Surface *info_menu, t_draw_i *info, t_sdl *sdl)
{
	info->color = sdl_initrgb(105, 105, 105, 255);
	info->rect = sdl_initrect(0, SEP_H + 1, IM_W, SEP_H);
	info->text = TTF_RenderText_Blended(sdl->text_bar, "Camera infos", \
					info->color);
	if (sdl_myfillrect(info_menu, &info->rect, COLOR_SEP) < 0)
		errors(ERR_SDL, "sdl_myfillrect failed --");
	info->rect = sdl_initrect(10, 10 * SEP_H + SEP_H, IM_W - 40, SEP_H);
	if (sdl_myfillrect(info_menu, &info->rect, DISABLE) < 0)
		errors(ERR_SDL, "sdl_myfillrect failed --");
	info->rect = sdl_initrect(10, 12 * SEP_H + SEP_H, IM_W - 40, SEP_H);
	if (sdl_myfillrect(info_menu, &info->rect, ENABLE) < 0)
		errors(ERR_SDL, "sdl_myfillrect failed --");
	info->rect = sdl_initrect(2, SEP_H, IM_W, SEP_H);
	if (SDL_BlitSurface(info->text, NULL, info_menu, &info->rect))
		errors(ERR_SDL, "SDL_BlitSurface info_menu failed --");
	SDL_FreeSurface(info->text);
	info->rect = sdl_initrect(20, 14 * SEP_H + SEP_H, IM_W - 40, SEP_H);
	if (sdl_myfillrect(info_menu, &info->rect, COLOR_SEP) < 0)
		errors(ERR_SDL, "sdl_myfillrect failed --");
	info->color = sdl_initrgb(192, 192, 192, 255);
}

static char	*which_filters(int fil)
{
	if (fil == 1)
		return (ft_strdup("Cartoon"));
	if (fil == 2)
		return (ft_strdup("Sepia"));
	if (fil == 3)
		return (ft_strdup("B&W"));
	return (ft_strdup(""));
}

char		*choose_info(int i, t_rt *rt, t_sdl *sdl)
{
	(void)sdl;
	if (i == 1)
		return (vector2string(&rt->eye.pos));
	if (i == 3)
		return (vector2string(&rt->eye.rot));
	if (i == 5)
		return (ft_dtoa(rt->config.focus_dist, 3));
	if (i == 7)
		return (ft_dtoa(rt->config.aperture, 3));
	if (i == 9)
	{
		if (rt->config.effects)
			return (ft_strdup("Disable"));
		else
			return (ft_strdup("Enable"));
	}
	if (i == 11)
		return (ft_strdup("Take a pic!"));
	if (i == 13)
		return (rt->config.aa == 0 ? ft_strdup("1") : ft_itoa(rt->config.aa));
	if (i == 17)
		return (which_filters(sdl->filters));
	return (NULL);
}

SDL_Rect	choose_rect(char *vec)
{
	if (ft_strcmp(vec, "1") == 0 || ft_strcmp(vec, "0") == 0)
	{
		return (sdl_initrect(20 + BUTTON_W / 2, 14 * SEP_H + SEP_H, BUTTON_W, \
				SEP_H - 2));
	}
	if (ft_strcmp(vec, "4") == 0)
	{
		return (sdl_initrect(20 + BUTTON_W + 10 + BUTTON_W / 2, \
				14 * SEP_H + SEP_H, BUTTON_W, SEP_H - 2));
	}
	if (ft_strcmp(vec, "8") == 0)
	{
		return (sdl_initrect(20 + 2 * BUTTON_W + 20 + BUTTON_W / 2, \
				14 * SEP_H + SEP_H, BUTTON_W, SEP_H - 2));
	}
	if (ft_strcmp(vec, "12") == 0)
	{
		return (sdl_initrect(20 + BUTTON_W / 2, 15 * SEP_H + SEP_H, BUTTON_W, \
				SEP_H - 2));
	}
	return (choose_rect2(vec));
}

SDL_Rect	choose_rect2(char *vec)
{
	if (ft_strcmp(vec, "16") == 0)
	{
		return (sdl_initrect(20 + BUTTON_W + 10 + BUTTON_W / 2, \
				15 * SEP_H + SEP_H, BUTTON_W, SEP_H - 2));
	}
	if (ft_strcmp(vec, "20") == 0)
	{
		return (sdl_initrect(20 + 2 * BUTTON_W + 20 + BUTTON_W / 2, \
				15 * SEP_H + SEP_H, BUTTON_W, SEP_H - 2));
	}
	return (sdl_initrect(20 + BUTTON_W / 2, 16 * SEP_H + SEP_H, BUTTON_W, \
				SEP_H - 2));
}
