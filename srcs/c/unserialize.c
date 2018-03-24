/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unserialize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 15:59:36 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/02/27 17:41:48 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			ft_unserialize_int(int i, t_buffer *buff)
{
	ft_memcpy(&i, buff->data + buff->next, sizeof(int));
	buff->next += sizeof(int);
	return (i);
}

double		ft_unserialize_double(double d, t_buffer *buff)
{
	ft_memcpy(&d, buff->data + buff->next, sizeof(double));
	buff->next += sizeof(double);
	return (d);
}

uint32_t	ft_unserialize_uint32t(uint32_t u, t_buffer *buff)
{
	ft_memcpy(&u, buff->data + buff->next, sizeof(uint32_t));
	buff->next += sizeof(uint32_t);
	return (u);
}

void		ft_unserialize_t_color(t_color *c, t_buffer *buff)
{
	c->r = ft_unserialize_int(c->r, buff);
	c->g = ft_unserialize_int(c->g, buff);
	c->b = ft_unserialize_int(c->b, buff);
	c->c = ft_unserialize_int(c->c, buff);
}

void		ft_unserialize_t_vector(t_vector *v, t_buffer *buff)
{
	v->x = ft_unserialize_double(v->x, buff);
	v->y = ft_unserialize_double(v->y, buff);
	v->z = ft_unserialize_double(v->z, buff);
}
