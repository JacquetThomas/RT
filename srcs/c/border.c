/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 17:53:25 by cjacquet          #+#    #+#             */
/*   Updated: 2018/03/09 17:58:27 by cjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		create_border(SDL_Surface *border, t_sdl *sdl)
{
	t_draw_i	cross;

	cross.color = sdl_initrgb(255, 255, 255, 255);
	cross.rect = sdl_initrect(0, 0, CROSS_W, SEP_H);
	cross.text = TTF_RenderText_Blended(sdl->text_bar, "  X", cross.color);
	if (sdl_myfillrect(border, &cross.rect, DISABLE) < 0)
		errors(ERR_SDL, "sdl_myfillrect failed --");
	if (SDL_BlitSurface(cross.text, NULL, border, NULL))
		errors(ERR_SDL, "SDL_BlitSurface info_info failed --");
	SDL_FreeSurface(cross.text);
	cross.rect = sdl_initrect(CROSS_W, 0, CROSS_W, SEP_H);
	cross.text = TTF_RenderText_Blended(sdl->text_bar, "  __", cross.color);
	if (sdl_myfillrect(border, &cross.rect, COLOR_BG) < 0)
		errors(ERR_SDL, "sdl_myfillrect failed --");
	cross.rect = sdl_initrect(CROSS_W, -5, CROSS_W, SEP_H);
	if (SDL_BlitSurface(cross.text, NULL, border, &cross.rect))
		errors(ERR_SDL, "SDL_BlitSurface info_info failed --");
	SDL_FreeSurface(cross.text);
	cross.color = sdl_initrgb(105, 105, 105, 255);
	cross.text = TTF_RenderText_Blended(sdl->text_bar, PROGRAM_NAME, \
			cross.color);
	cross.rect = sdl_initrect(WIN_W / 2 - 5, 0, WIN_H / 2, SEP_H);
	if (SDL_BlitSurface(cross.text, NULL, border, &cross.rect))
		errors(ERR_SDL, "SDL_BlitSurface info_info failed --");
	SDL_FreeSurface(cross.text);
}

static void	update_open2(t_sdl *sdl, t_draw_i *box)
{
	box->rect = sdl_initrect(sdl->show_info ? \
		WIN_W - IM_W - BOX_W : WIN_W - BOX_W, (SEP_H + 1) * 2, BOX_W, BOX_H);
	if (SDL_BlitSurface(sdl->open, NULL, sdl->screen, &box->rect))
		errors(ERR_SDL, "SDL_BlitSurface text on open failed --");
}

void		update_open(t_sdl *sdl)
{
	t_draw_i	box;

	box.color = sdl_initrgb(192, 192, 192, 255);
	box.rect = sdl_initrect(2, -3, BOX_W, BOX_H);
	if ((sdl_myfillrect(sdl->open, NULL, COLOR_BG)) < 0)
		errors(ERR_SDL, "SDL_FillRect failed --");
	box.text = TTF_RenderText_Blended(sdl->text_bar, sdl->show_help ?\
			WINK_L : WINK_R, box.color);
	if (SDL_BlitSurface(box.text, NULL, sdl->open, &box.rect))
		errors(ERR_SDL, "SDL_BlitSurface text on open failed --");
	SDL_FreeSurface(box.text);
	box.rect = sdl_initrect(sdl->show_help ? \
			HM_W : 0, (SEP_H + 1) * 2, BOX_W, BOX_H);
	if (SDL_BlitSurface(sdl->open, NULL, sdl->screen, &box.rect))
		errors(ERR_SDL, "SDL_BlitSurface text on open failed --");
	box.rect = sdl_initrect(2, -3, BOX_W, BOX_H);
	if ((sdl_myfillrect(sdl->open, NULL, COLOR_BG)) < 0)
		errors(ERR_SDL, "SDL_FillRect failed --");
	box.text = TTF_RenderText_Blended(sdl->text_bar, sdl->show_info ? \
			WINK_R : WINK_L, box.color);
	if (SDL_BlitSurface(box.text, NULL, sdl->open, &box.rect))
		errors(ERR_SDL, "SDL_BlitSurface text on open failed --");
	SDL_FreeSurface(box.text);
	update_open2(sdl, &box);
}
