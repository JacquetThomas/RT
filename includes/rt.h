/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 14:54:15 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/17 19:21:48 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "clustering.h"
# include "libft.h"
# include "rt_defines.h"
# include "rt_structures.h"

void			ft_get_scene(char *file, t_parser *p);
void			ft_clean_tab(t_parser *p);
void			ft_implode(t_parser *p, char *sep, int nb_line);
int				ft_get_int(int *i, int fd);
int				ft_get_double(double *d, int fd);
void			ft_get_focus(t_vector *v, t_eye eye, t_rt *rt);
void			ft_get_conf(t_config *cfg, char *file);
int				ft_objectid(char *str);
int				ft_check_color(char *str);
int				ft_check_numbers(char *str, int j);
int				ft_get_obj_color(t_rt *rt, double light);
int				sdl_events(t_sdl *sdl, t_key *keys, t_rt *rt);
long			errors(const int err, const char *comment);
double			ft_limits(double nb, double min, double max);
double			ft_vector_len(t_vector v);
void			ft_parse(char *file, t_data *data);
void			ft_init_data(t_data *data);
long			ft_error(int error, int line);
int				ft_comment(char *str);
int				ft_get_bm(char **tab, double *bm, int *i, int *line);
int				ft_get_negative(char **tab, int *neg, int *i, int *line);
int				ft_get_size(char **tab, t_vector *size, int *i, int *line);
int				ft_get_rgb(char *line, int *l);
int				ft_get_color(char **tab, t_color *color, int *i, int *line);
int				ft_get_coord(char **tab, t_vector *pos, int *i, int *line);
int				ft_get_rotation(char **tab, t_vector *rot, int *i, int *line);
int				ft_get_intensity(char **tab, double *intensity, int *i, \
																	int *line);
int				ft_get_reflection(char **tab, double *ref, int *i, int *line);
int				ft_get_opacity(char **tab, double *transp, int *i, int *line);
int				ft_get_specularity(char **tab, double *spec, int *i, int *line);
int				ft_get_perturbation(char **tab, double *np, int *i, int *line);
void			ft_get_p_texture(t_object *obj, char *str, int *line);
int				ft_get_texture(char **tab, t_object *obj, int *i, int *line);
int				ft_get_noise(char **tab, t_noise *noise, int *i, int *line);
void			ft_get_object(char **tab, t_rt *rt, int *i, int j[12]);
void			ft_get_sphere(char **tab, t_data *data, int *i, int *line);
void			ft_get_plane(char **tab, t_data *data, int *i, int *line);
void			ft_get_cone(char **tab, t_data *data, int *i, int *line);
void			ft_get_cylinder(char **tab, t_data *data, int *i, int *line);
void			ft_get_cube(char **tab, t_data *data, int *i, int *line);
void			ft_get_fov(t_eye *eye, int *fd);
void			ft_get_data2(char **tab, t_data *data, int *line, int *i);
void			*ft_calc(void *param);
void			ft_default_value(t_object *objs, t_rt *rt);
void			ft_check_collisions(t_rt *rt, t_object *objs, t_light *l);
void			ft_rotate_y(t_eye *eye, t_vector *m, int i);
void			ft_rotate_z(t_eye *eye, t_vector *m, int i);
void			ft_calc_dir_vec(t_eye *eye, t_vector *m);
void			ft_init_struct(t_data *data);
int				ft_translation(char **tab, t_vector *pos, int *i, int *line);
void			ft_color(t_color *c, int color);
void			client(t_client client);
void			server(t_data data, int nb_cli);
t_client		init_client(char *host);
void			print_struct(t_rt rt);
t_vector		ft_new_vector(double x, double y, double z);
t_vector		ft_vector_product(t_vector v1, t_vector v2);
t_vector		ft_add_vector(t_vector v1, t_vector v2);
t_vector		ft_sub_vector(t_vector v1, t_vector v2);
t_vector		ft_norm_vector(t_vector v);
t_vector		ft_scale_vector(t_vector v, double scale);
int				sdl_update_menus(t_key *keys, t_sdl *sdl, t_rt *rt);
void			create_help(SDL_Surface *help_menu, t_sdl *sdl);
void			create_info(SDL_Surface *info_menu, t_sdl *sdl);
void			create_border(SDL_Surface *border, t_sdl *sdl);
void			create_open(t_sdl *sdl);
SDL_Rect		choose_rect(char *vec);
SDL_Rect		choose_rect2(char *vec);
char			*choose_info(int i, t_rt *rt, t_sdl *sdl);
void			update_open(t_sdl *sdl);
void			put_pixel(SDL_Surface *surf, int x, int y, Uint32 color);
char			*vector2string(t_vector *vec);
void			update_info(t_sdl *sdl, t_rt *rt);
int				on_button(int x, int y);
int				on_exit_cross(int x, int y);
int				on_title_bar(int x, int y);
int				on_reduce(int x, int y);
int				on_screenshot(int x, int y);
int				on_button_aa(int x, int y, t_rt *rt);
int				on_button_filter(int x, int y, t_sdl *sdl);
int				sdl_mouse_up(t_sdl *sdl, t_key *keys, t_rt *rt);
int				sdl_mouse_down(t_sdl *sdl, t_key *keys, t_rt *rt);
int				save_picture(t_sdl *sdl);
void			last_oneb(t_sdl *sdl, t_draw_i *info);
void			create_loading(t_sdl *sdl);
int				loading(t_sdl *sdl);
void			filters_button(t_sdl *sdl, t_draw_i *info, int i, char *vec);
SDL_Rect		filter_hightrect(int fil);
void			ft_bw(uint32_t *img);
void			ft_sepia(uint32_t *img);
void			ft_cartoon(uint32_t *img);
void			call_filters(int fil, SDL_Surface *eff, SDL_Surface *draw);
int				gx(uint32_t *img, int k, int j, int c);
int				gy(uint32_t *img, int k, int j, int c);
int				ft_limit_color(int color);
void			check_truc(const char **tab, int nb_line);

#endif
