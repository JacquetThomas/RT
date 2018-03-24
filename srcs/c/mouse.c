/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 20:05:48 by cjacquet          #+#    #+#             */
/*   Updated: 2018/03/17 11:54:51 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sdl_mouse_up3(t_sdl *sdl, int *i_only, t_rt *rt)
{
	if (sdl->show_info && \
			sdl->event.button.button == SDL_BUTTON_LEFT && \
			on_button_filter(sdl->event.button.x, sdl->event.button.y, sdl))
		*i_only = 1;
	if (*i_only)
	{
		update_info(sdl, rt);
		sdl_run(sdl);
	}
}

int			sdl_mouse_up2(t_sdl *sdl, t_key *keys, t_rt *rt, int old_aa)
{
	int		i_only;

	if (!(i_only = 0) && sdl->show_info && \
			sdl->event.button.button == SDL_BUTTON_LEFT && \
			on_screenshot(sdl->event.button.x, sdl->event.button.y))
		keys->p = 1;
	if (sdl->event.button.button == SDL_BUTTON_LEFT && sdl->drag)
	{
		SDL_CaptureMouse(FALSE);
		sdl->drag = 0;
	}
	if (sdl->show_info && \
			sdl->event.button.button == SDL_BUTTON_LEFT && \
			(rt->config.aa = on_button_aa(sdl->event.button.x, \
			sdl->event.button.y, rt)))
	{
		if (old_aa != rt->config.aa)
		{
			i_only = 1;
			keys->r = 1;
			return (1);
		}
	}
	sdl_mouse_up3(sdl, &i_only, rt);
	return (0);
}

int			sdl_mouse_up(t_sdl *sdl, t_key *keys, t_rt *rt)
{
	int		old_aa;

	old_aa = rt->config.aa;
	if (sdl->event.button.button == SDL_BUTTON_LEFT && \
			on_exit_cross(sdl->event.button.x, sdl->event.button.y))
		exit(EXIT_SUCCESS);
	if (sdl->event.button.button == SDL_BUTTON_LEFT && \
			on_reduce(sdl->event.button.x, sdl->event.button.y))
	{
		SDL_MinimizeWindow(sdl->window);
	}
	if (sdl->show_info && \
			sdl->event.button.button == SDL_BUTTON_LEFT && \
			on_button(sdl->event.button.x, sdl->event.button.y))
	{
		keys->r = 1;
		rt->config.effects = (rt->config.effects) ? 0 : 1;
		return (1);
	}
	return (sdl_mouse_up2(sdl, keys, rt, old_aa));
}

int			sdl_mouse_down(t_sdl *sdl, t_key *keys, t_rt *rt)
{
	(void)rt;
	(void)keys;
	if (sdl->event.button.button == SDL_BUTTON_LEFT && \
			on_title_bar(sdl->event.button.x, sdl->event.button.y) && \
			!sdl->drag)
	{
		SDL_CaptureMouse(TRUE);
		SDL_GetGlobalMouseState(&sdl->mouse_pos.x, &sdl->mouse_pos.y);
		sdl->drag = 1;
	}
	return (0);
}
