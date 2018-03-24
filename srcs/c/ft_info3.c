/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_info3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 19:44:41 by cjacquet          #+#    #+#             */
/*   Updated: 2018/03/17 10:05:56 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		create_ieven(t_draw_i *info, int i, char **tab, t_sdl *sdl)
{
	info->color = sdl_initrgb(192, 192, 192, 255);
	info->text = TTF_RenderText_Blended(sdl->text_bar, tab[i], info->color);
	info->rect = sdl_initrect(2, (i + 1) * SEP_H + SEP_H, IM_W, SEP_H);
}

void		create_iodd(t_draw_i *info, int i, char **tab, t_sdl *sdl)
{
	info->rect = sdl_initrect(10, (i + 1) * SEP_H + SEP_H, IM_W, SEP_H);
	if (i == 9 || i == 11)
	{
		info->color = sdl_initrgb(105, 105, 105, 255);
		info->rect = sdl_initrect(IM_W / 3, (i + 1) * SEP_H + SEP_H, \
				IM_W, SEP_H);
	}
	info->text = TTF_RenderText_Blended(sdl->plain_text, tab[i], info->color);
}

void		last_oneb(t_sdl *sdl, t_draw_i *info)
{
	info->text = TTF_RenderText_Blended(sdl->plain_text, "__", \
								info->color);
	info->rect = sdl_initrect(20, 16 * SEP_H + SEP_H, BUTTON_W, SEP_H - 2);
	if (sdl_myfillrect(sdl->info_menu, &info->rect, COLOR_SEP) < 0)
		errors(ERR_SDL, "sdl_myfillrect failed --");
	info->rect = sdl_initrect(20 + BUTTON_W / 2, \
					16 * SEP_H + SEP_H, (IM_W + 20) / 3, SEP_H);
	if (SDL_BlitSurface(info->text, NULL, sdl->info_menu, &info->rect))
		errors(ERR_SDL, "SDL_BlitSurface info_info failed --");
	SDL_FreeSurface(info->text);
}

static void	filters_while(t_sdl *sdl, t_draw_i *info, int i, char **tab)
{
	int	nb;

	nb = -1;
	i += 1;
	while (++nb < 3)
	{
		info->text = TTF_RenderText_Blended(sdl->plain_text, tab[nb], \
								info->color);
		info->rect = sdl_initrect(20 + nb * BUTTON_W + nb * 10, \
						i * SEP_H + SEP_H, BUTTON_W, SEP_H - 2);
		if (sdl_myfillrect(sdl->info_menu, &info->rect, COLOR_SEP) < 0)
			errors(ERR_SDL, "sdl_myfillrect failed --");
		info->rect = sdl_initrect(20 + nb * BUTTON_W + nb * 10 + 4, \
						i * SEP_H + SEP_H, (IM_W + 20) / 3, SEP_H);
		if (SDL_BlitSurface(info->text, NULL, sdl->info_menu, &info->rect))
			errors(ERR_SDL, "SDL_BlitSurface info_info failed --");
		SDL_FreeSurface(info->text);
	}
}

void		filters_button(t_sdl *sdl, t_draw_i *info, int i, char *vec)
{
	static char	*tab[3] = {"Cartoon", "Sepia", "B&W"};

	info->color = sdl_initrgb(105, 105, 105, 255);
	filters_while(sdl, info, i, tab);
	info->color = sdl_initrgb(255, 255, 255, 255);
	info->text = TTF_RenderText_Blended(sdl->plain_text, vec, info->color);
	info->rect = filter_hightrect(sdl->filters);
}
