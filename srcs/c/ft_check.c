/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 15:17:23 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/18 13:28:18 by cjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_check_numbers(char *str, int j)
{
	int		i;

	i = -1;
	if (j == 0)
	{
		while (str[++i])
			if ((str[i] < 48 || str[i] > 57) && str[i] != '-' && str[i] != '.')
				return (0);
	}
	else if (j == 1)
	{
		while (str[++i])
			if ((str[i] < 48 || str[i] > 57) && str[i] != '-' && str[i] != ',' \
															&& str[i] != '.')
				return (0);
	}
	else if (j == 2)
	{
		while (str[++i])
			if ((str[i] < 48 || str[i] > 57) && (str[i] < 97 || str[i] > 102))
				return (0);
	}
	return (1);
}

int		ft_objectid(char *str)
{
	if (ft_strcmp(str, "sphere:") == 0)
		return (0);
	else if (ft_strcmp(str, "plan:") == 0)
		return (1);
	else if (ft_strcmp(str, "cone:") == 0)
		return (2);
	else if (ft_strcmp(str, "cylinder:") == 0)
		return (3);
	else if (ft_strcmp(str, "light:") == 0)
		return (4);
	else
		return (-1);
}

void	ft_default_value(t_object *objs, t_rt *rt)
{
	int		i;

	i = -1;
	while (++i < rt->nb_obj)
	{
		objs[i].rot = (!ft_vector_len(objs[i].rot)) ? (t_vector){1, 0, 0, 0} : \
																	objs[i].rot;
	}
	i = -1;
	while (++i < rt->nb_light)
		(rt->lights[i].intensity < 0) ? rt->lights[i].intensity = INTENSITY : 0;
	rt->eye.aspect = 1.5;
	rt->eye.fov = FOV;
	rt->eye.zoom = ZOOM;
	rt->config.effects = 1;
	(ft_vector_len(rt->eye.rot) == 0.0) ? ft_error(2, 0) : 0;
}

int		ft_countword(char *str, char c)
{
	int		nb;
	int		i;

	i = 0;
	nb = 0;
	while (str[i])
	{
		(str[i] == c) ? nb++ : 0;
		i++;
	}
	return (nb);
}

int		ft_check_color(char *str)
{
	if (str[0] == '0' && str[1] == 'x')
	{
		if (ft_check_numbers(str + 2, 2) == 0)
			return (-1);
		else
			return (0);
	}
	else if (ft_check_numbers(str, 1) == 0)
		return (-1);
	else if (ft_countword(str, ',') == 2)
		return (1);
	else
		return (2);
}
