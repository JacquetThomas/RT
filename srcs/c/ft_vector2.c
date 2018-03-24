/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:05:29 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/16 15:24:30 by cjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	ft_scale_vector(t_vector v, double scale)
{
	v.x *= scale;
	v.y *= scale;
	v.z *= scale;
	return (v);
}

double		ft_vector_len(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

char		*vector2string(t_vector *vec)
{
	char		*string;
	char		*tmp;
	char		*tmpp;
	static char	*comma = ", ";

	string = ft_dtoa(vec->x, 3);
	string = ft_strcat(string, comma);
	tmpp = ft_dtoa(vec->y, 3);
	tmpp = ft_strcat(tmpp, comma);
	tmp = ft_strjoin(string, tmpp);
	free(string);
	free(tmpp);
	tmpp = ft_dtoa(vec->z, 3);
	string = ft_strjoin(tmp, tmpp);
	free(tmp);
	free(tmpp);
	return (string);
}
