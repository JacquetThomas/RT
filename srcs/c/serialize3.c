/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:39:17 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/17 14:49:12 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_serialize_t_config(t_config c, t_buffer *buff)
{
	ft_serialize_t_vector(c.focus, buff);
	ft_serialize_double(c.ambient, buff);
	ft_serialize_double(c.aperture, buff);
	ft_serialize_double(c.focus_dist, buff);
	ft_serialize_int(c.aa, buff);
	ft_serialize_int(c.dof, buff);
	ft_serialize_int(c.dof_int, buff);
	ft_serialize_int(c.shadows, buff);
	ft_serialize_int(c.effects, buff);
	ft_serialize_int(c.show_focus, buff);
	ft_serialize_int(c.lights, buff);
}

void	ft_serialize_t_rt(t_rt r, t_buffer *buff)
{
	int		i;

	i = -1;
	while (++i < OBJS_MAX)
		ft_serialize_t_object(r.objects[i], buff);
	i = -1;
	while (++i < LGTS_MAX)
		ft_serialize_t_light(r.lights[i], buff);
	ft_serialize_t_eye(r.eye, buff);
	ft_serialize_t_vector(r.m[0], buff);
	ft_serialize_t_vector(r.m[1], buff);
	ft_serialize_t_vector(r.m[2], buff);
	ft_serialize_t_config(r.config, buff);
	ft_serialize_int(r.offset, buff);
	ft_serialize_int(r.nb_cli, buff);
	ft_serialize_int(r.nb_obj, buff);
	ft_serialize_int(r.nb_light, buff);
	ft_serialize_int(r.line, buff);
}

void	ft_serialize_rand(double rand[MAX_RAND], t_buffer *buff)
{
	int		i;

	i = -1;
	while (++i < MAX_RAND)
		ft_serialize_double(rand[i], buff);
}
