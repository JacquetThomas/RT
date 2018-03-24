/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unserialize2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:41:19 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/02/27 17:42:44 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_unserialize_t_light(t_light *l, t_buffer *buff)
{
	ft_unserialize_t_vector(&l->pos, buff);
	l->intensity = ft_unserialize_double(l->intensity, buff);
}

void		ft_unserialize_t_noise(t_noise *n, t_buffer *buff)
{
	n->oct = ft_unserialize_int(n->oct, buff);
	n->freq = ft_unserialize_double(n->freq, buff);
	n->persis = ft_unserialize_double(n->persis, buff);
	n->intensity = ft_unserialize_double(n->intensity, buff);
}

void		ft_unserialize_t_object(t_object *o, t_buffer *buff)
{
	ft_unserialize_t_vector(&o->pos, buff);
	ft_unserialize_t_vector(&o->rot, buff);
	ft_unserialize_t_vector(&o->size, buff);
	ft_unserialize_t_noise(&o->noise, buff);
	ft_unserialize_t_color(&o->color, buff);
	o->reflect = ft_unserialize_double(o->reflect, buff);
	o->refract = ft_unserialize_double(o->refract, buff);
	o->transp = ft_unserialize_double(o->transp, buff);
	o->spec = ft_unserialize_double(o->spec, buff);
	o->np = ft_unserialize_double(o->np, buff);
	o->bm = ft_unserialize_double(o->bm, buff);
	o->type = ft_unserialize_int(o->type, buff);
	o->p_texture = ft_unserialize_int(o->p_texture, buff);
}

void		ft_unserialize_t_eye(t_eye *e, t_buffer *buff)
{
	ft_unserialize_t_vector(&e->pos, buff);
	ft_unserialize_t_vector(&e->rot, buff);
	e->fov = ft_unserialize_double(e->fov, buff);
	e->zoom = ft_unserialize_double(e->zoom, buff);
	e->aspect = ft_unserialize_double(e->aspect, buff);
}
