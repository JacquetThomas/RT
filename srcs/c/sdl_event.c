/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 15:25:40 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/18 10:13:38 by cjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_move(t_key *keys, t_eye *eye, t_vector *m, t_rt *rt)
{
	int		i;

	i = ((keys->shift) ? 2.0 : 1.0);
	if (keys->w)
		eye->pos = ft_add_vector(eye->pos, ft_scale_vector(m[0], SPEED_V * i));
	else if (keys->s)
		eye->pos = ft_sub_vector(eye->pos, ft_scale_vector(m[0], SPEED_V * i));
	if (keys->a)
		eye->pos = ft_add_vector(eye->pos, ft_scale_vector(m[1], SPEED_V * i));
	else if (keys->d)
		eye->pos = ft_sub_vector(eye->pos, ft_scale_vector(m[1], SPEED_V * i));
	if (keys->lctrl)
		eye->pos = ft_sub_vector(eye->pos, ft_scale_vector(m[2], SPEED_H * i));
	else if (keys->space)
		eye->pos = ft_add_vector(eye->pos, ft_scale_vector(m[2], SPEED_H * i));
	keys->e ? ft_rotate_y(eye, m, 1) : 0;
	keys->q ? ft_rotate_y(eye, m, -1) : 0;
	keys->down ? ft_rotate_z(eye, m, 1) : 0;
	keys->up ? ft_rotate_z(eye, m, -1) : 0;
	if (keys->plus && rt->config.show_focus)
		rt->config.focus_dist += (0.5 * i);
	else if (keys->minus && rt->config.show_focus)
		rt->config.focus_dist += (-0.5 * i);
	ft_get_focus(&rt->config.focus, *eye, rt);
}

static int	sdl_keyboard2(t_key *keys, t_vector *m, t_rt *rt, const Uint8 *s)
{
	(s[SDL_SCANCODE_H]) ? keys->h = 1 : 0;
	(s[SDL_SCANCODE_I]) ? keys->i = 1 : 0;
	(s[SDL_SCANCODE_P]) ? keys->p = 1 : 0;
	(s[SDL_SCANCODE_ESCAPE]) ? exit(EXIT_SUCCESS) : 0;
	(s[SDL_SCANCODE_1]) ? (rt->config.effects = (++rt->config.effects % 2)) && \
												(rt->config.show_focus = 0) : 0;
	(s[SDL_SCANCODE_2]) ? (rt->config.show_focus = (++rt->config.show_focus % \
											2)) && (rt->config.effects = 0) : 0;
	ft_move(keys, &rt->eye, m, rt);
	if (s[SDL_SCANCODE_S] || s[SDL_SCANCODE_W] || \
		s[SDL_SCANCODE_A] || s[SDL_SCANCODE_D] || \
		s[SDL_SCANCODE_SPACE] || s[SDL_SCANCODE_LCTRL] || \
		s[SDL_SCANCODE_E] || s[SDL_SCANCODE_Q] || \
		s[SDL_SCANCODE_1] || s[SDL_SCANCODE_UP] || \
		s[SDL_SCANCODE_DOWN] || s[SDL_SCANCODE_2] || \
		s[SDL_SCANCODE_MINUS] || s[SDL_SCANCODE_KP_PLUS] || \
		s[SDL_SCANCODE_H] || s[SDL_SCANCODE_I])
		return (1);
	return (0);
}

static int	sdl_keyboard(t_key *keys, t_vector *m, t_rt *rt)
{
	const Uint8		*state = SDL_GetKeyboardState(NULL);

	ft_bzero(keys, sizeof(t_key));
	keys->w = (state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_S]);
	keys->s = (state[SDL_SCANCODE_S] && !state[SDL_SCANCODE_W]);
	keys->a = (state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D]);
	keys->d = (state[SDL_SCANCODE_D] && !state[SDL_SCANCODE_A]);
	keys->lctrl = (state[SDL_SCANCODE_LCTRL] && !state[SDL_SCANCODE_SPACE]);
	keys->space = (state[SDL_SCANCODE_SPACE] && !state[SDL_SCANCODE_LCTRL]);
	keys->e = (state[SDL_SCANCODE_E] && !state[SDL_SCANCODE_Q]);
	keys->q = (state[SDL_SCANCODE_Q] && !state[SDL_SCANCODE_E]);
	keys->down = (state[SDL_SCANCODE_DOWN] && !state[SDL_SCANCODE_UP]);
	keys->up = (state[SDL_SCANCODE_UP] && !state[SDL_SCANCODE_DOWN]);
	keys->shift = state[SDL_SCANCODE_LSHIFT];
	keys->plus = state[SDL_SCANCODE_KP_PLUS] && !state[SDL_SCANCODE_KP_MINUS];
	keys->minus = state[SDL_SCANCODE_MINUS] && !state[SDL_SCANCODE_KP_PLUS];
	return (sdl_keyboard2(keys, m, rt, state));
}

void		sdl_drag(t_sdl *sdl, t_yx pos)
{
	if (sdl->drag && sdl->event.type == SDL_MOUSEMOTION)
	{
		SDL_GetGlobalMouseState(&pos.x, &pos.y);
		SDL_GetWindowPosition(sdl->window, &sdl->win_pos.x, \
				&sdl->win_pos.y);
		SDL_SetWindowPosition(sdl->window, sdl->win_pos.x + \
				(pos.x - sdl->mouse_pos.x), sdl->win_pos.y + \
				(pos.y - sdl->mouse_pos.y));
		sdl->mouse_pos.x = pos.x;
		sdl->mouse_pos.y = pos.y;
	}
}

int			sdl_events(t_sdl *sdl, t_key *keys, t_rt *rt)
{
	t_yx	pos;
	int		update;

	pos.x = 0;
	pos.y = 0;
	update = EVENT_IDLE;
	if (SDL_PollEvent(&sdl->event))
	{
		if (sdl->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE || \
				sdl->event.type == SDL_QUIT)
			exit(EXIT_SUCCESS);
		if (sdl->event.type == SDL_KEYDOWN)
			if (sdl_keyboard(keys, rt->m, rt) && \
					sdl_update_menus(keys, sdl, rt))
				update = EVENT_UPDATE;
		if (sdl->event.type == SDL_MOUSEBUTTONUP)
			(sdl_mouse_up(sdl, keys, rt)) ? update = EVENT_UPDATE : 0;
		if (sdl->event.type == SDL_MOUSEBUTTONDOWN)
			(sdl_mouse_down(sdl, keys, rt)) ? update = EVENT_UPDATE : 0;
		sdl_drag(sdl, pos);
		keys->p = (keys->p) ? save_picture(sdl) : 0;
		return (update);
	}
	return (EVENT_IDLE);
}
