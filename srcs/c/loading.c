/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 17:39:49 by cjacquet          #+#    #+#             */
/*   Updated: 2018/03/12 17:40:54 by cjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	create_loading(t_sdl *sdl)
{
	t_draw_i	load;

	load.color = sdl_initrgb(255, 255, 255, 255);
	load.text = TTF_RenderText_Blended(sdl->text_bar, "Loading ...", \
			load.color);
	load.rect = sdl_initrect(20, 20, sdl->size.x - 40, sdl->size.y - 40);
	if (!(sdl->load = SDL_CreateRGBSurfaceWithFormat(0, \
					sdl->size.x, sdl->size.y, 32, \
					sdl->screen->format->format)))
		errors(ERR_SDL, "SDL_CreateRGBSurface menu_help failed --");
	if ((sdl_myfillrect(sdl->load, NULL, COLOR_SEP)) < 0)
		errors(ERR_SDL, "SDL_FillRect failed --");
	if ((sdl_myfillrect(sdl->load, &load.rect, COLOR_BG)) < 0)
		errors(ERR_SDL, "SDL_FillRect failed --");
	load.rect = sdl_initrect(sdl->size.x / 2 - 40, sdl->size.y / 2, \
			sdl->size.x, sdl->size.y);
	if (SDL_BlitSurface(load.text, NULL, sdl->load, &load.rect))
		errors(ERR_SDL, "SDL_BlitSurface help_menu3 failed --");
	SDL_FreeSurface(load.text);
}

int		loading(t_sdl *sdl)
{
	if (SDL_BlitSurface(sdl->load, NULL, sdl->screen, NULL))
		errors(ERR_SDL, "SDL_BlitSurface help_menu3 failed --");
	if (SDL_UpdateWindowSurface(sdl->window))
		errors(ERR_SDL, "SDL_UpdateWindowSurface failed --");
	return (1);
}
