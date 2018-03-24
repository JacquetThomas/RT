/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_conf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:41:05 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/17 16:52:30 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_get_focus(t_vector *v, t_eye eye, t_rt *rt)
{
	static int		o = 0;

	o = (o == 0) ? rt->nb_obj : o;
	*v = ft_add_vector(eye.pos, ft_scale_vector(eye.rot, \
														rt->config.focus_dist));
	rt->objects[o].type = FOCUS;
	rt->objects[o].pos = *v;
	rt->objects[o].size = ft_new_vector(-1, -1, -1);
	rt->objects[o].rot = eye.rot;
	rt->objects[o].color = (t_color){200, 0, 0, 200};
	rt->objects[o].transp = 75;
	(o == rt->nb_obj) ? rt->nb_obj++ : 0;
}

void		ft_parse_conf(t_config *cfg, int fd, int set[9], char *line)
{
	while (get_next_line(fd, &line))
	{
		if (ft_strcmp(line, "focus_dist:") == 0 && !set[0])
			set[0] = ft_get_double(&cfg->focus_dist, fd);
		else if (ft_strcmp(line, "ambient_light:") == 0 && !set[1])
			set[1] = ft_get_double(&cfg->ambient, fd);
		else if (ft_strcmp(line, "aperture:") == 0 && !set[2])
			set[2] = ft_get_double(&cfg->aperture, fd);
		else if (ft_strcmp(line, "anti_aliasing:") == 0 && !set[3])
			set[3] = ft_get_int(&cfg->aa, fd);
		else if (ft_strcmp(line, "depth_of_field:") == 0 && !set[4])
			set[4] = ft_get_int(&cfg->dof, fd);
		else if (ft_strcmp(line, "dof_intensity:") == 0 && !set[5])
			set[5] = ft_get_int(&cfg->dof_int, fd);
		else if (ft_strcmp(line, "soft_shadows:") == 0 && !set[6])
			set[6] = ft_get_int(&cfg->shadows, fd);
		else if (ft_strcmp(line, "effects:") == 0 && !set[7])
			set[7] = ft_get_int(&cfg->effects, fd);
		else if (ft_strcmp(line, "show_ligths:") == 0 && !set[6])
			set[8] = ft_get_int(&cfg->lights, fd);
		else
			errors(-1, ft_strjoin("config file invalid, unknown tag: ", line));
		free(line);
	}
}

void		ft_warning_conf(t_config *cfg, int set[9])
{
	if ((cfg->dof == 0 && cfg->dof_int) || (cfg->dof == 0 && cfg->aperture))
		ft_putstr("Warning: depth of field disabled\n");
	if (cfg->dof && !set[2])
	{
		ft_putstr("Warning: aperture not set in .cfg file.\n");
		ft_putstr("\t Default aperture set (");
		ft_putnbr(APERTURE);
		ft_putstr(")\n");
		cfg->aperture = APERTURE;
	}
	if (cfg->dof && !set[5])
	{
		ft_putstr("Warning: depth of fiel intensity not set in .cfg file.\n");
		ft_putstr("\t Default intensity set (");
		ft_putnbr(DOF_INT);
		ft_putstr(")\n");
		cfg->dof_int = DOF_INT;
	}
	cfg->aa -= cfg->aa % 4;
}

void		ft_check_conf(t_config *cfg, int set[9])
{
	(cfg->focus_dist <= 0 && cfg->dof == 1 && set[0]) ? \
									errors(-1, "invalid focusing distance") : 0;
	((cfg->ambient < 0 || cfg->ambient > 1) && set[1]) ? \
						errors(-1, "invalid ambient light (min 0, max 1)") : 0;
	(cfg->aperture < 1.4 && set[2]) ? errors(-1, "invalid aperture (min 1.4)") \
																			: 0;
	(cfg->aa < 4 && set[3]) ? errors(-1, "invalid anti-aliasing value (min 4)")\
																			: 0;
	((cfg->dof < 0 || cfg->dof > 1) && set[4]) ? \
					errors(-1, "depth_of_field invalid (on: 1, off: 0)") : 0;
	((cfg->dof_int < 1 || cfg->dof_int > 1000000) && set[5]) ? \
					errors(-1, "invalid depth of field intensity (min 1)") : 0;
	((cfg->shadows < 0 || cfg->shadows > 1) && set[6]) ? \
						errors(-1, "soft_shadows invalid (on: 1, off: 0)") : 0;
	((cfg->effects < 0 || cfg->effects > 1) && set[7]) ? \
							errors(-1, "effects invalid (on: 1, off: 0)") : 0;
	((cfg->lights < 0 || cfg->lights > 1) && set[8]) ? \
							errors(-1, "lights invalid (on: 1, off: 0)") : 0;
	ft_warning_conf(cfg, set);
}

void		ft_get_conf(t_config *cfg, char *file)
{
	char	*cfg_file;
	int		fd;
	int		set[9];

	fd = 0;
	ft_bzero(set, sizeof(set));
	if (!(cfg_file = malloc((ft_strlen(file) + 1) * sizeof(char))))
		ft_error(3, 0);
	cfg_file = ft_strcpy(cfg_file, file);
	cfg_file = ft_strrev(cfg_file);
	cfg_file[0] = 'g';
	cfg_file[1] = 'f';
	cfg_file[2] = 'c';
	cfg_file = ft_strrev(cfg_file);
	if ((fd = open(cfg_file, O_RDONLY)) > 0)
	{
		ft_parse_conf(cfg, fd, set, 0);
		close(fd);
		ft_check_conf(cfg, set);
	}
	free(cfg_file);
}
