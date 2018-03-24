/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:24:34 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/17 11:40:01 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			sdl_init_window(t_sdl *sdl)
{
	SDL_GetWindowSize(sdl->window, &sdl->size.x, &sdl->size.y);
	SDL_FreeSurface(sdl->screen);
	if (!(sdl->screen = SDL_GetWindowSurface(sdl->window)))
		errors(ERR_SDL, "SDL_GetWindowSurface failed --");
	SDL_FreeSurface(sdl->draw_surface);
	free(sdl->pixels);
	if (!(sdl->pixels = ft_memalloc(BPP * sdl->size.x * sdl->size.y)))
		errors(ERR_SYS, 0);
	if (!(sdl->draw_surface = SDL_CreateRGBSurfaceFrom((void*)sdl->pixels, \
					sdl->size.x, sdl->size.y, BPP, 4 * sdl->size.x, \
					0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000)))
		errors(ERR_SDL, "SDL_CreateRGBSurface failed --");
	if (!(sdl->eff = SDL_CreateRGBSurfaceWithFormat(0, sdl->size.x, sdl->size.y,
					32, sdl->screen->format->format)))
		errors(ERR_SDL, "SDL_CreateRGBSurface eff failed --");
}

void			sdl_init(t_sdl *sdl, const char *window_name)
{
	if (TTF_Init() || SDL_Init(SDL_INIT_VIDEO))
		errors(ERR_SDL, "Init failed --");
	if (!(sdl->window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, \
	SDL_WINDOWPOS_CENTERED, sdl->size.x, sdl->size.y, SDL_WINDOW_BORDERLESS)))
		errors(ERR_SDL, "SDL_CreateWindow failed --");
	if (!(sdl->text_bar = \
				TTF_OpenFont("./font/roboto/Roboto-BoldCondensedItalic.ttf", \
					20)))
		errors(ERR_SDL, "TTF_OpenFont failed --");
	if (!(sdl->plain_text = \
				TTF_OpenFont("./font/roboto/Roboto-BoldCondensedItalic.ttf", \
					18)))
		errors(ERR_SDL, "TTF_OpenFont failed --");
	sdl_init_window(sdl);
	sdl_init_menus(sdl);
}

void			sdl_run(t_sdl *sdl)
{
	SDL_Rect	srcrect;

	srcrect = sdl_initrect(0, 0, HM_W, sdl->size.y);
	if (sdl->filters)
	{
		call_filters(sdl->filters, sdl->eff, sdl->draw_surface);
		if (SDL_BlitSurface(sdl->eff, NULL, sdl->screen, NULL))
			errors(ERR_SDL, "SDL_BlitSurface failed --");
	}
	else if (SDL_BlitSurface(sdl->draw_surface, NULL, sdl->screen, NULL))
		errors(ERR_SDL, "SDL_BlitSurface failed --");
	if (sdl->show_help == 1)
		if (SDL_BlitSurface(sdl->help_menu, NULL, sdl->screen, &srcrect))
			errors(ERR_SDL, "SDL_BlitSurface help_menu failed --");
	srcrect = sdl_initrect(WIN_W - IM_W, 0, IM_W, sdl->size.y);
	if (sdl->show_info == 1)
		if (SDL_BlitSurface(sdl->info_menu, NULL, sdl->screen, &srcrect))
			errors(ERR_SDL, "SDL_BlitSurface info_menu failed --");
	if (SDL_BlitSurface(sdl->border, NULL, sdl->screen, NULL))
		errors(ERR_SDL, "SDL_BlitSurface failed --");
	update_open(sdl);
	if (SDL_UpdateWindowSurface(sdl->window))
		errors(ERR_SDL, "SDL_UpdateWindowSurface failed --");
}

void			sdl_end(t_sdl *sdl)
{
	free(sdl->pixels);
	SDL_FreeSurface(sdl->screen);
	SDL_FreeSurface(sdl->draw_surface);
	SDL_FreeSurface(sdl->border);
	SDL_FreeSurface(sdl->help_menu);
	SDL_FreeSurface(sdl->info_menu);
	SDL_FreeSurface(sdl->open);
	SDL_FreeSurface(sdl->eff);
	SDL_FreeSurface(sdl->load);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
}

void			put_pixel(SDL_Surface *surf, int x, int y, Uint32 color)
{
	Uint32		*pix;

	if (x >= 0 && y >= 0 && x < surf->w && y < surf->h)
	{
		pix = (Uint32 *)surf->pixels;
		pix[surf->w * y + x] = color;
	}
}
