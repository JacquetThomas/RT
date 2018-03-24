/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 18:19:27 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/11 19:12:00 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_get_sphere(char **tab, t_data *data, int *i, int *line)
{
	int		j[12];
	int		k;

	k = data->rt.nb_obj;
	ft_bzero(&j, sizeof(j));
	data->rt.objects[k].type = SPHERE;
	while (ft_strcmp(tab[++(*i)], "/sphere") != 0)
	{
		data->rt.line = *line;
		(ft_strcmp(tab[*i], "-") == 0) ? *line += 1 : \
											ft_get_object(tab, &data->rt, i, j);
	}
	data->rt.nb_obj++;
	(j[1] == 0) ? ft_putstr("sphere size not set, ") : 0;
	(j[0] == 0) ? ft_putstr("sphere position not set, ") : 0;
	(!j[0] || !j[1]) ? ft_error(2, *line) : 0;
}

void	ft_get_plane(char **tab, t_data *data, int *i, int *line)
{
	int		j[12];
	int		k;

	k = data->rt.nb_obj;
	ft_bzero(&j, sizeof(j));
	data->rt.objects[k].type = PLANE;
	while (ft_strcmp(tab[++(*i)], "/plane") != 0)
	{
		data->rt.line = *line;
		(ft_strcmp(tab[*i], "-") == 0) ? *line += 1 : \
											ft_get_object(tab, &data->rt, i, j);
	}
	data->rt.nb_obj++;
	(!j[0]) ? ft_putstr("plane position not set, ") : 0;
	(!j[0]) ? ft_error(2, *line) : 0;
}

void	ft_get_cone(char **tab, t_data *data, int *i, int *line)
{
	int		j[12];
	int		k;

	k = data->rt.nb_obj;
	ft_bzero(&j, sizeof(j));
	data->rt.objects[k].type = CONE;
	while (ft_strcmp(tab[++(*i)], "/cone") != 0)
	{
		data->rt.line = *line;
		(ft_strcmp(tab[*i], "-") == 0) ? *line += 1 : \
											ft_get_object(tab, &data->rt, i, j);
	}
	data->rt.nb_obj++;
	(j[1] == 0) ? ft_putstr("cone size not set, ") : 0;
	(j[0] == 0) ? ft_putstr("cone position not set, ") : 0;
	(!j[0] || !j[1]) ? ft_error(2, *line) : 0;
}

void	ft_get_cylinder(char **tab, t_data *data, int *i, int *line)
{
	int		j[12];
	int		k;

	k = data->rt.nb_obj;
	ft_bzero(&j, sizeof(j));
	data->rt.objects[k].type = CYLINDER;
	while (ft_strcmp(tab[++(*i)], "/cylinder") != 0)
	{
		data->rt.line = *line;
		(ft_strcmp(tab[*i], "-") == 0) ? *line += 1 : \
											ft_get_object(tab, &data->rt, i, j);
	}
	data->rt.nb_obj++;
	(j[1] == 0) ? ft_putstr("cylinder size not set, ") : 0;
	(j[0] == 0) ? ft_putstr("cylinder position not set, ") : 0;
	(!j[0] || !j[1]) ? ft_error(2, *line) : 0;
}

void	ft_get_cube(char **tab, t_data *data, int *i, int *line)
{
	int		j[12];
	int		k;

	k = data->rt.nb_obj;
	ft_bzero(&j, sizeof(j));
	data->rt.objects[k].type = CUBE;
	while (ft_strcmp(tab[++(*i)], "/cube") != 0)
	{
		data->rt.line = *line;
		(ft_strcmp(tab[*i], "-") == 0) ? *line += 1 : \
											ft_get_object(tab, &data->rt, i, j);
	}
	data->rt.nb_obj++;
	(j[0] == 0) ? ft_putstr("cube position not set, ") : 0;
	(j[1] == 0) ? ft_putstr("cube size not set, ") : 0;
	(j[9] != 0) ? ft_putstr("you can't change the orientation of composite \
															item <cube>\n") : 0;
	(!j[0] || !j[1] || j[9]) ? ft_error(2, *line) : 0;
}
