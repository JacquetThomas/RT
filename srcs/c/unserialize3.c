/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unserialize3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:41:13 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/17 14:49:32 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_unserialize_t_config(t_config *c, t_buffer *buff)
{
	ft_unserialize_t_vector(&c->focus, buff);
	c->ambient = ft_unserialize_double(c->ambient, buff);
	c->aperture = ft_unserialize_double(c->aperture, buff);
	c->focus_dist = ft_unserialize_double(c->focus_dist, buff);
	c->aa = ft_unserialize_int(c->aa, buff);
	c->dof = ft_unserialize_int(c->dof, buff);
	c->dof_int = ft_unserialize_int(c->dof_int, buff);
	c->shadows = ft_unserialize_int(c->shadows, buff);
	c->effects = ft_unserialize_int(c->effects, buff);
	c->show_focus = ft_unserialize_int(c->show_focus, buff);
	c->lights = ft_unserialize_int(c->lights, buff);
}

void		ft_unserialize_t_rt(t_rt *r, t_buffer *buff)
{
	int		i;

	i = -1;
	while (++i < OBJS_MAX)
		ft_unserialize_t_object(&r->objects[i], buff);
	i = -1;
	while (++i < LGTS_MAX)
		ft_unserialize_t_light(&r->lights[i], buff);
	ft_unserialize_t_eye(&r->eye, buff);
	ft_unserialize_t_vector(&r->m[0], buff);
	ft_unserialize_t_vector(&r->m[1], buff);
	ft_unserialize_t_vector(&r->m[2], buff);
	ft_unserialize_t_config(&r->config, buff);
	r->offset = ft_unserialize_int(r->offset, buff);
	r->nb_cli = ft_unserialize_int(r->nb_cli, buff);
	r->nb_obj = ft_unserialize_int(r->nb_obj, buff);
	r->nb_light = ft_unserialize_int(r->nb_light, buff);
	r->line = ft_unserialize_int(r->line, buff);
}

void		ft_unserialize_rand(double rand[MAX_RAND], t_buffer *buff)
{
	int		i;

	i = -1;
	while (++i < MAX_RAND)
		rand[i] = ft_unserialize_double(rand[i], buff);
}
