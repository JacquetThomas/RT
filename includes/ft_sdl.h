/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sdl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 11:55:45 by agrumbac          #+#    #+#             */
/*   Updated: 2018/03/17 10:01:41 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SDL_H
# define FT_SDL_H

/*
** ********************************** SDL **************************************
** BPP				BytesPerPixel : is 32 for (uint32_t*)sdl->pixels
**
** ********************************** functions ********************************
** void		sdl_init(t_sdl *sdl, const char *window_name);
** 					initialize sdl window
** void		sdl_run(t_sdl *sdl);
** 					draw sdl->pixels to sdl->screen of sdl->window
** void		sdl_end(t_sdl *sdl);
** 					terminate and free all sdl environment
**
** void		sdl_init_window(t_sdl *sdl);
** 					initializes window, use in case of resize event
** *****************************************************************************
*/

# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <stdint.h>

# define BPP			32
# define PROGRAM_NAME	"RT"
# define WINK_L			"<<"
# define WINK_R			">>"
# define COLOR_BG		0xFF696969
# define COLOR_SEP		0xFFC0C0C0
# define COLOR_BUT		0xFF9C9C9C
# define TEST_COLOR		0xFFFF00FF
# define DISABLE		0xFFD8636F
# define ENABLE			0xFF5CB85C

typedef struct			s_yx
{
	int					y;
	int					x;
}						t_yx;

typedef struct			s_sdl
{
	SDL_Window			*window;
	SDL_Surface			*screen;
	SDL_Surface			*draw_surface;
	SDL_Surface			*border;
	SDL_Surface			*help_menu;
	SDL_Surface			*info_menu;
	SDL_Surface			*open;
	SDL_Surface			*load;
	SDL_Surface			*eff;
	TTF_Font			*text_bar;
	TTF_Font			*plain_text;
	int					show_help;
	int					show_info;
	int					drag;
	SDL_Event			event;
	t_yx				size;
	t_yx				win_pos;
	t_yx				mouse_pos;
	uint32_t			*pixels;
	int					filters;
}						t_sdl;

typedef struct			s_draw_i
{
	SDL_Rect			rect;
	SDL_Surface			*text;
	SDL_Color			color;
}						t_draw_i;

void					sdl_init(t_sdl *sdl, const char *window_name);
void					sdl_run(t_sdl *sdl);
void					sdl_end(t_sdl *sdl);

void					sdl_init_window(t_sdl *sdl);
SDL_Color				sdl_initrgb(int r, int g, int b, int a);
void					sdl_init_menus(t_sdl *sdl);
int						sdl_myfillrect(SDL_Surface *surf, SDL_Rect *rect, \
																Uint32 color);
SDL_Rect				sdl_initrect(int x, int y, int w, int h);
void					print_irect(SDL_Surface *info_menu, t_draw_i *info, \
																	t_sdl *sdl);
void					create_ieven(t_draw_i *info, int i, char **tab, \
																	t_sdl *sdl);
void					create_iodd(t_draw_i *info, int i, char **tab, \
																	t_sdl *sdl);

#endif
