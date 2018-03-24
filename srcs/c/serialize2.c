/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:36:13 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/02/27 17:39:26 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_serialize_t_vector(t_vector v, t_buffer *buff)
{
	ft_serialize_double(v.x, buff);
	ft_serialize_double(v.y, buff);
	ft_serialize_double(v.z, buff);
}

void	ft_serialize_t_light(t_light l, t_buffer *buff)
{
	ft_serialize_t_vector(l.pos, buff);
	ft_serialize_double(l.intensity, buff);
}

void	ft_serialize_t_noise(t_noise n, t_buffer *buff)
{
	ft_serialize_int(n.oct, buff);
	ft_serialize_double(n.freq, buff);
	ft_serialize_double(n.persis, buff);
	ft_serialize_double(n.intensity, buff);
}

void	ft_serialize_t_object(t_object o, t_buffer *buff)
{
	ft_serialize_t_vector(o.pos, buff);
	ft_serialize_t_vector(o.rot, buff);
	ft_serialize_t_vector(o.size, buff);
	ft_serialize_t_noise(o.noise, buff);
	ft_serialize_t_color(o.color, buff);
	ft_serialize_double(o.reflect, buff);
	ft_serialize_double(o.refract, buff);
	ft_serialize_double(o.transp, buff);
	ft_serialize_double(o.spec, buff);
	ft_serialize_double(o.np, buff);
	ft_serialize_double(o.bm, buff);
	ft_serialize_int(o.type, buff);
	ft_serialize_int(o.p_texture, buff);
}

void	ft_serialize_t_eye(t_eye e, t_buffer *buff)
{
	ft_serialize_t_vector(e.pos, buff);
	ft_serialize_t_vector(e.rot, buff);
	ft_serialize_double(e.fov, buff);
	ft_serialize_double(e.zoom, buff);
	ft_serialize_double(e.aspect, buff);
}
