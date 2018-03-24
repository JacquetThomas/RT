/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_structures.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 14:46:14 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/18 13:07:29 by cjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCTURES_H
# define RT_STRUCTURES_H

# include "cl.h"
# include "ft_sdl.h"

typedef struct		s_norm
{
	int				i;
	char			*vec;
	Uint32			col;
}					t_norm;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
	int				c;
}					t_color;

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
	uint32_t		p : 32;
}					t_vector;

typedef struct		s_light
{
	t_vector		pos;
	double			intensity;
	uint64_t		p : 64;
	uint64_t		p1 : 64;
	uint64_t		p2 : 64;
}					t_light;

typedef struct		s_noise
{
	int				oct;
	double			freq;
	double			persis;
	double			intensity;
}					t_noise;

typedef struct		s_object
{
	t_vector		pos;
	t_vector		rot;
	t_vector		size;
	t_noise			noise;
	t_color			color;
	double			reflect;
	double			refract;
	double			transp;
	double			spec;
	double			np;
	double			bm;
	int				type;
	int				negative;
	int				p_texture;
	uint32_t		p : 32;
	uint64_t		p1 : 64;
	uint64_t		p2 : 64;
}					t_object;

typedef struct		s_eye
{
	t_vector		pos;
	t_vector		rot;
	double			fov;
	double			zoom;
	double			aspect;
	uint64_t		p : 64;
}					t_eye;

typedef struct		s_config
{
	t_vector		focus;
	double			ambient;
	double			aperture;
	double			focus_dist;
	int				aa;
	int				dof;
	int				dof_int;
	int				shadows;
	int				effects;
	int				show_focus;
	int				lights;
	uint64_t		p : 64;
}					t_config;

typedef struct		s_rt
{
	t_object		objects[OBJS_MAX];
	t_light			lights[LGTS_MAX];
	t_eye			eye;
	t_vector		m[3];
	t_config		config;
	int				offset;
	int				nb_cli;
	int				nb_obj;
	int				nb_light;
	int				line;
	uint64_t		p : 64;
}					t_rt;

typedef struct		s_parser
{
	char			**tab;
	char			**tab2;
	char			*data;
	int				nb_line;
}					t_parser;

typedef struct		s_key
{
	int				w;
	int				s;
	int				d;
	int				a;
	int				space;
	int				lctrl;
	int				q;
	int				e;
	int				i;
	int				h;
	int				r;
	int				p;
	int				down;
	int				up;
	int				shift;
	int				plus;
	int				minus;
}					t_key;

typedef struct		s_data
{
	t_rt			rt;
	t_cl			cl;
	t_sdl			sdl;
	t_key			keys;
	double			rand[MAX_RAND];
}					t_data;

#endif
