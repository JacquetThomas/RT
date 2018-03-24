/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_info.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 11:55:45 by cjacquet          #+#    #+#             */
/*   Updated: 2018/03/16 15:35:11 by cjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		create_info(SDL_Surface *info_menu, t_sdl *sdl)
{
	t_draw_i	info;
	int			i;
	static char	*tab[17] = {"Camera position", "NULL", "Camera orientation", \
	"NULL", "Distance to focus point", "NULL", "Aperture", "NULL", "Effects", \
	"Disable", "Screenshot", "Take a pic!", "Anti-Aliasing", "", "", "", \
	"Filters"};

	print_irect(info_menu, &info, sdl);
	i = -1;
	while (++i < 17)
	{
		if ((i % 2) == 0)
			create_ieven(&info, i, tab, sdl);
		else
			create_iodd(&info, i, tab, sdl);
		if (info.text && \
				SDL_BlitSurface(info.text, NULL, info_menu, &info.rect))
			errors(ERR_SDL, "SDL_BlitSurface help_info3 failed --");
		SDL_FreeSurface(info.text);
	}
}

static void	adding_while(t_sdl *sdl, t_draw_i *info, int i, char **tab)
{
	int	nb;
	int	flag;

	nb = -1;
	flag = 1;
	while (++nb < 6)
	{
		info->text = TTF_RenderText_Blended(sdl->plain_text, tab[nb], \
								info->color);
		if (nb > 2 && (flag = 2))
			nb -= 3;
		info->rect = sdl_initrect(20 + nb * BUTTON_W + nb * 10, \
						(i + flag) * SEP_H + SEP_H, BUTTON_W, SEP_H - 2);
		if (sdl_myfillrect(sdl->info_menu, &info->rect, COLOR_SEP) < 0)
			errors(ERR_SDL, "sdl_myfillrect failed --");
		info->rect = sdl_initrect(20 + nb * BUTTON_W + nb * 10 + BUTTON_W / 2, \
						(i + flag) * SEP_H + SEP_H, (IM_W + 20) / 3, SEP_H);
		if (SDL_BlitSurface(info->text, NULL, sdl->info_menu, &info->rect))
			errors(ERR_SDL, "SDL_BlitSurface info_info failed --");
		SDL_FreeSurface(info->text);
		if (flag == 2)
			nb += 3;
	}
	last_oneb(sdl, info);
}

void		adding_button(t_sdl *sdl, t_draw_i *info, int i, char *vec)
{
	static char	*tab[6] = {"1", "4", "8", "12", "16", "20"};

	info->color = sdl_initrgb(105, 105, 105, 255);
	adding_while(sdl, info, i, tab);
	info->color = sdl_initrgb(255, 255, 255, 255);
	info->text = TTF_RenderText_Blended(sdl->plain_text, vec, info->color);
	info->rect = choose_rect(vec);
}

static void	update_odd(t_rt *rt, t_draw_i *info, t_norm *n, t_sdl *sdl)
{
	SDL_FreeSurface(info->text);
	info->rect = sdl_initrect(20, (n->i + 1) * SEP_H + SEP_H, IM_W - 40, SEP_H);
	n->col = ENABLE;
	if (n->i == 13)
		adding_button(sdl, info, n->i, n->vec);
	else if (n->i == 17)
		filters_button(sdl, info, n->i, n->vec);
	else
	{
		if (n->i == 9)
			n->col = rt->config.effects ? DISABLE : ENABLE;
		if (sdl_myfillrect(sdl->info_menu, &info->rect, n->col) < 0)
			errors(ERR_SDL, "sdl_myfillrect failed --");
		info->color = sdl_initrgb(255, 255, 255, 255);
		info->text = TTF_RenderText_Blended(sdl->plain_text, n->vec, \
				info->color);
		info->rect = sdl_initrect(IM_W / 3, (n->i + 1) * SEP_H + SEP_H, \
				IM_W, SEP_H);
	}
}

void		update_info(t_sdl *sdl, t_rt *rt)
{
	t_draw_i	info;
	t_norm		n;

	info.color = sdl_initrgb(192, 192, 192, 255);
	n.i = 1;
	while (n.i < 18)
	{
		info.rect = sdl_initrect(4, (n.i + 1) * (SEP_H) + SEP_H, IM_W, SEP_H);
		if (sdl_myfillrect(sdl->info_menu, &info.rect, COLOR_BG) < 0)
			errors(ERR_SDL, "sdl_myfillrect failed --");
		n.vec = choose_info(n.i, rt, sdl);
		info.text = TTF_RenderText_Blended(sdl->plain_text, n.vec, info.color);
		if (n.i == 9 || n.i == 11 || n.i == 13 || n.i >= 15)
			update_odd(rt, &info, &n, sdl);
		if (info.text && \
				SDL_BlitSurface(info.text, NULL, sdl->info_menu, &info.rect))
			errors(ERR_SDL, "SDL_BlitSurface info_info failed --");
		free(n.vec);
		SDL_FreeSurface(info.text);
		n.i = (n.i + 2 == 15) ? n.i + 4 : n.i + 2;
	}
}
