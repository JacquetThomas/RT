/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 19:13:34 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/17 16:58:39 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H_CL
# define RT_H_CL

# define GLOBAL_X		1
# define GLOBAL_Y		0
# define WIN_H			800
# define WIN_W			1200

# define MAX_BOUNCES	100
# define PI				3.141596
# define MAX_RAND		5000
# define OBJS_MAX		50
# define LGTS_MAX		15

# define SPHERE			0
# define PLANE			1
# define CONE			2
# define CYLINDER		3
# define CUBE			4
# define FOCUS			5

# define CHESSBOARD 	1
# define BRICKS 		2
# define WOOD 			3
# define MARBLE 		4

# define BRICK_W		0.5
# define BRICK_H		0.1
# define MORTAR_W		0.015
# define MORTAR_H		0.0075
# define CHESS_SIZE		0.01

# define RL				1.0
# define BL				1.0
# define GL				1.0

# define FOCAL_LENGTH	30.0

typedef double3		t_vector;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
	int				c;
}					t_color;

typedef struct		s_equation
{
	double			a;
	double			b;
	double			c;
	double			delta;
}					t_equation;

typedef struct		s_ray
{
	t_vector		n;
	t_vector		pos;
	t_vector		dir;
	t_vector		coldir;
	t_vector		colpos;
	double			t;
	double			dist;
	double			otherside;
	int				id;
	int				bounces;
	int				coltype;
}					t_ray;

typedef struct		s_light
{
	t_vector		pos;
	double			intensity;
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
}					t_object;

typedef struct		s_eye
{
	t_vector		pos;
	t_vector		rot;
	double			fov;
	double			zoom;
	double			aspect;
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
}					t_rt;
t_color					ft_get_color_per_ray(double2 aa_coords, const int2      size, __global t_rt *rt, __constant double *rand);
t_color					ft_anti_aliasing(const int2     coords, __global t_rt *rt, __constant double *rand, const int2  size);
void 						print_data_infos(__global t_rt *rt, const int2 coords, t_ray ray);
static double			ft_lerp(double d, t_vector v);
static t_color			ft_focus_plane(__global t_rt *rt, t_ray *ray, __constant double *rand);
static t_ray			ft_init_ray(__global t_rt *rt, const double2 coords, const int2 size);
static double			ft_rand(const int x);
static double			ft_rand2(const int x, const int y);
static double			ft_rand3(const int x, const int y, const int z);
static t_vector			ft_normale(__global t_rt *rt, __global t_object *obj, const t_vector hit, const t_ray *ray, __constant double *rand);
static double			ft_calc_light(__global t_rt *rt, __global t_object *obj, __global t_light *l, const t_ray *ray, __constant double *rand);
static void				ft_check_collisions_2(__global t_rt *rt, __global t_light *l, t_ray *ray);
static void				ft_sphere_col(const t_object obj, t_ray *ray);
static void				ft_plane_col(const t_object obj, t_ray *ray);
static void				ft_cone_col(const t_object obj, t_ray *ray);
static void				ft_cube_col(const t_object obj, t_ray *ray);
static void				ft_cyl_col(const t_object obj, t_ray *ray);
static double			ft_shadow_col(t_rt *tmp, t_ray *r);
static double			ft_hard_shadows(__global t_rt *rt, const t_vector hit, __global t_light *light);
static double			ft_soft_shadows(__global t_rt *rt, const t_vector hit, __global t_light *light, __constant double *rand);
static void				ft_reflect_ray(__global t_rt *rt, t_ray *ray, __constant double *rand);
static void				ft_refract_ray(t_ray *ray, const double n1, const double n2, const t_vector n);
static t_color			ft_procedural_texture(__global t_rt *rt, t_ray ray, __global t_object *obj, __constant double *rand);
static t_color			ft_bricks(double2 coords, __constant double *rand, __global const t_object *obj);
static t_color			ft_marble(const t_vector hit, const __global t_object *obj);
static t_color			ft_wood(const t_vector hit, const __global t_object *obj);
static double			ft_perlin_noise(const t_vector hit);
static double2			ft_get_text_coords(const t_vector hit, __global t_object *obj, const t_ray *ray, __constant double *rand, __global t_rt *rt);
static double2			ft_sphere_text_coords(const t_vector hit, const __global t_object *obj);
static double2			ft_cone_text_coords(const t_vector hit, const __global t_object *obj, const t_ray *ray, __constant double *rand);
static double2			ft_cyl_text_coords(const t_vector hit, const __global t_object *obj, const t_ray *ray, __constant double *rand);
static double2			ft_plane_text_coords(const t_vector hit, const __global t_object *obj);
static t_color			ft_color(__global t_rt *rt, const t_ray ray, const double l, __constant double *rand);
static t_color			ft_ref_color(__global t_rt *rt, t_ray *ray, const double ref, __constant double *rand);
static t_color			ft_refract_color(__global t_rt *rt, const double n1, const double n2, t_ray *ray);
static t_color			ft_reflection(__global t_rt *rt, t_ray *ray, __constant double *rand);
static t_color			ft_transp_color(__global t_rt *rt, t_ray *ray, __constant double *rand);
static t_color			ft_transparency(__global t_rt *rt, const double transp, t_ray *ray, __constant double *rand);
static t_vector			ft_proc_perturb(__global t_rt *rt, t_vector n, __global t_object *obj, __constant double *rand, const t_vector hit, const t_ray *ray);
static t_vector			ft_bricks_pert(const double2 coords, __constant double *rand);
static void				ft_perturbation(__global t_rt *rt, t_vector *n, __global t_object *obj, const t_vector hit);
static void				check_col_neg(__global t_rt *rt, t_ray *ray, int hit);

#endif
