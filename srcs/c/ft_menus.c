/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:55:45 by cjacquet          #+#    #+#             */
/*   Updated: 2018/03/18 10:13:25 by cjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sdl_init_menus(t_sdl *sdl)
{
	if (!(sdl->help_menu = SDL_CreateRGBSurfaceWithFormat(0, HM_W, sdl->size.y,
					32, sdl->screen->format->format)))
		errors(ERR_SDL, "SDL_CreateRGBSurface menu_help failed --");
	if (!(sdl->open = SDL_CreateRGBSurfaceWithFormat(0, BOX_W, BOX_H,
					32, sdl->screen->format->format)))
		errors(ERR_SDL, "SDL_CreateRGBSurface open failed --");
	if (!(sdl->border = SDL_CreateRGBSurfaceWithFormat(0, WIN_W, SEP_H,
					32, sdl->screen->format->format)))
		errors(ERR_SDL, "SDL_CreateRGBSurface menu_help failed --");
	if (!(sdl->info_menu = SDL_CreateRGBSurfaceWithFormat(0, IM_W, sdl->size.y,
					32, sdl->screen->format->format)))
		errors(ERR_SDL, "SDL_CreateRGBSurface menu_info failed --");
	if ((sdl_myfillrect(sdl->help_menu, NULL, COLOR_BG)) < 0)
		errors(ERR_SDL, "SDL_FillRect failed --");
	if ((sdl_myfillrect(sdl->info_menu, NULL, COLOR_BG)) < 0)
		errors(ERR_SDL, "SDL_FillRect failed --");
	if ((sdl_myfillrect(sdl->border, NULL, COLOR_SEP)) < 0)
		errors(ERR_SDL, "SDL_FillRect failed --");
	if ((sdl_myfillrect(sdl->open, NULL, COLOR_BG)) < 0)
		errors(ERR_SDL, "SDL_FillRect failed --");
	create_help(sdl->help_menu, sdl);
	create_info(sdl->info_menu, sdl);
	create_border(sdl->border, sdl);
	sdl->show_help = 0;
	sdl->show_info = 0;
}

int			sdl_update_menus(t_key *keys, t_sdl *sdl, t_rt *rt)
{
	if (keys->h)
		sdl->show_help = (sdl->show_help) ? 0 : 1;
	if (keys->i)
	{
		update_info(sdl, rt);
		sdl->show_info = (sdl->show_info) ? 0 : 1;
	}
	return (1);
}

SDL_Rect	filter_hightrect(int fil)
{
	if (fil == 1)
		return (sdl_initrect(24, 18 * SEP_H + SEP_H, BUTTON_W, SEP_H - 2));
	if (fil == 2)
	{
		return (sdl_initrect(20 + BUTTON_W + 14, \
				18 * SEP_H + SEP_H, BUTTON_W, SEP_H - 2));
	}
	if (fil == 3)
	{
		return (sdl_initrect(20 + 2 * BUTTON_W + 24, \
				18 * SEP_H + SEP_H, BUTTON_W, SEP_H - 2));
	}
	return (sdl_initrect(24, 18 * SEP_H + SEP_H, BUTTON_W, SEP_H - 2));
}
