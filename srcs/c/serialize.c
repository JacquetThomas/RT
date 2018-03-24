/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 13:49:10 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/02/27 17:36:30 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_init_buffer(t_buffer *buff, int size)
{
	if ((buff->data = (void *)malloc(size)) == NULL)
		errors(ERR_SYS, "Serialization init failed\n");
	ft_bzero(buff->data, size);
	buff->size = size;
	buff->next = 0;
}

void	ft_serialize_int(int i, t_buffer *buff)
{
	ft_memcpy(buff->data + buff->next, &i, sizeof(int));
	buff->next += sizeof(int);
}

void	ft_serialize_double(double d, t_buffer *buff)
{
	ft_memcpy(buff->data + buff->next, &d, sizeof(double));
	buff->next += sizeof(double);
}

void	ft_serialize_uint32t(uint32_t u, t_buffer *buff)
{
	ft_memcpy(buff->data + buff->next, &u, sizeof(uint32_t));
	buff->next += sizeof(uint32_t);
}

void	ft_serialize_t_color(t_color c, t_buffer *buff)
{
	ft_serialize_int(c.r, buff);
	ft_serialize_int(c.g, buff);
	ft_serialize_int(c.b, buff);
	ft_serialize_int(c.c, buff);
}
