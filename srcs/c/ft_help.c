/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquet <cjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 11:55:45 by cjacquet          #+#    #+#             */
/*   Updated: 2018/03/09 18:16:26 by cjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	create_help2(SDL_Surface *help_menu, t_sdl *sdl, char **tab,
		t_draw_i *help)
{
	int	i;

	i = -1;
	help->color = sdl_initrgb(192, 192, 192, 255);
	while (++i < 20)
	{
		if (i == 0 || i == 7 || i == 12 || i == 15 || i == 17)
		{
			help->text = TTF_RenderText_Blended(sdl->text_bar, tab[i], \
					help->color);
			help->rect = sdl_initrect(2, (i + 1) * (SEP_H - 1) + SEP_H, HM_W, \
					SEP_H);
		}
		else
		{
			help->rect = sdl_initrect(10, (i + 1) * (SEP_H - 1) + SEP_H, HM_W, \
					SEP_H);
			help->text = TTF_RenderText_Blended(sdl->plain_text, tab[i], \
					help->color);
		}
		if (SDL_BlitSurface(help->text, NULL, help_menu, &help->rect))
			errors(ERR_SDL, "SDL_BlitSurface help_menu3 failed --");
		SDL_FreeSurface(help->text);
	}
}

void		create_help(SDL_Surface *help_menu, t_sdl *sdl)
{
	t_draw_i	help;
	static char	*tab[20] = {"Camera movements", "-Forward     : W", \
	"-Backward  : S", "-Left           : A", "-Right        : D", \
	"-Up            : Space bar", "-Down       : Ctlr", "Camera rotations", \
	"-Up       : Arrow up", "-Down  : Arrow down", "-Left    : Q", \
	"-Right : E", "Effects", "-Enable/Disable : 1", \
	"-Acceleration    : Shift", "Depth of field", "-Show : 2", "Other", \
	"-Open/Close Help : H", "-Open/Close Info  : I"};

	help.color = sdl_initrgb(105, 105, 105, 255);
	help.rect = sdl_initrect(0, SEP_H + 1, HM_W, SEP_H);
	help.text = TTF_RenderText_Blended(sdl->text_bar, "Available functions", \
			help.color);
	if (sdl_myfillrect(help_menu, &help.rect, COLOR_SEP) < 0)
		errors(ERR_SDL, "sdl_myfillrect failed --");
	help.rect = sdl_initrect(2, SEP_H, HM_W, SEP_H);
	if (SDL_BlitSurface(help.text, NULL, help_menu, &help.rect))
		errors(ERR_SDL, "SDL_BlitSurface help_menu2 failed --");
	SDL_FreeSurface(help.text);
	create_help2(help_menu, sdl, tab, &help);
	create_loading(sdl);
}
