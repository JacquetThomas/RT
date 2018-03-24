/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mysdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquet <cjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 11:55:45 by cjacquet          #+#    #+#             */
/*   Updated: 2018/03/09 19:59:08 by cjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static SDL_Rect	check_rect(SDL_Rect *rect, SDL_Surface *surf, int *y)
{
	SDL_Rect	r;

	*y = 0;
	if (!rect)
		r = sdl_initrect(0, 0, surf->w, surf->h);
	else
		r = sdl_initrect(rect->x, rect->y, rect->w, rect->h);
	return (r);
}

SDL_Color		sdl_initrgb(int r, int g, int b, int a)
{
	SDL_Color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

SDL_Rect		sdl_initrect(int x, int y, int w, int h)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}

int				sdl_myfillrect(SDL_Surface *surf, SDL_Rect *rect, Uint32 color)
{
	int			y;
	int			x;
	SDL_Rect	r;

	r = check_rect(rect, surf, &y);
	y = 0;
	while (y < r.h)
	{
		x = 0;
		while (x < r.w)
		{
			put_pixel(surf, x + r.x, y + r.y, color);
			++x;
		}
		++y;
	}
	return (0);
}
