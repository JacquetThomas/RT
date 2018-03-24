/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:27:08 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/13 15:27:41 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_get_size(char **tab, t_vector *size, int *i, int *line)
{
	char	**t;
	int		j;
	int		w;

	while (ft_strcmp(tab[++(*i)], "-") == 0)
		*line += 1;
	(!ft_check_numbers(tab[*i], 1)) ? ft_error(2, *line) : 0;
	w = ft_countwords(tab[*i], ',');
	t = ft_strsplit(tab[*i], ',');
	size->x = (w > 0) ? ft_atod(t[0]) : 0;
	size->y = (w > 1) ? ft_atod(t[1]) : 0;
	size->z = (w > 2) ? ft_atod(t[2]) : 0;
	j = -1;
	while (t[++j])
		free(t[j]);
	free(t);
	while (ft_strcmp(tab[++(*i)], "/size") != 0)
		(!ft_strcmp(tab[*i], "-")) ? *line += 1 : ft_error(2, *line);
	return (1);
}

int		ft_get_rgb(char *line, int *l)
{
	char	**t;
	int		c;
	cl_int3	i;

	c = 0;
	t = ft_strsplit(line, ',');
	(!t[0] || !t[1] || !t[2] || t[3]) ? ft_error(2, *l) : 0;
	i.x = ft_atoi(t[2]);
	i.y = ft_atoi(t[1]);
	i.z = ft_atoi(t[0]);
	(i.x < 0 || i.x > 255 || i.y < 0 || i.y > 255 || i.z < 0 || i.z > 255) ? \
															ft_error(2, *l) : 0;
	c = (0xff << 24 | i.x << 16 | i.y << 8 | i.z);
	free(t[0]);
	free(t[1]);
	free(t[2]);
	free(t);
	return (c);
}

int		ft_get_color(char **tab, t_color *color, int *i, int *line)
{
	int		format;

	while (ft_strcmp(tab[++(*i)], "-") == 0)
		*line += 1;
	(ft_comment(tab[*i])) ? ft_error(2, *line) : 0;
	format = ft_check_color(tab[*i]);
	if (format == 0 && ft_check_numbers(tab[*i] + 2, 2))
		color->c = 0xff << 24 | ft_atoi_base(tab[*i] + 2, 16);
	else if (format == 1 && ft_check_numbers(tab[*i], 1))
		color->c = ft_get_rgb(tab[*i], line);
	else if (format == 2 && ft_check_numbers(tab[*i], 0))
		color->c = 0xff << 24 | ft_atoi(tab[*i]);
	else
		ft_error(2, *line);
	color->r = color->c & 0x000000ff;
	color->g = color->c & 0x0000ff00;
	color->b = color->c & 0x00ff0000;
	(color->r < 0 || color->g < 0 || color->b < 0) ? ft_error(2, *line) : 0;
	while (ft_strcmp(tab[++(*i)], "/color") != 0)
		(!ft_strcmp(tab[(*i)], "-")) ? *line += 1 : ft_error(2, *line);
	return (1);
}

int		ft_get_coord(char **tab, t_vector *pos, int *i, int *line)
{
	char	**t;
	int		j;

	j = -1;
	while (ft_strcmp(tab[++(*i)], "-") == 0)
		*line += 1;
	(!ft_check_numbers(tab[(*i)], 1)) ? ft_error(2, *line) : 0;
	t = ft_strsplit(tab[*i], ',');
	(!t[0] || !t[1] || !t[2] || t[3]) ? ft_error(2, *line) : 0;
	pos->x = ft_atod(t[0]);
	pos->y = -ft_atod(t[1]);
	pos->z = ft_atod(t[2]);
	while (t[++j])
		free(t[j]);
	free(t);
	while (ft_strcmp(tab[++(*i)], "/position") != 0)
		(!ft_strcmp(tab[(*i)], "-")) ? *line += 1 : ft_error(2, *line);
	return (1);
}

int		ft_get_rotation(char **tab, t_vector *rot, int *i, int *line)
{
	char	**t;
	int		j;

	j = -1;
	while (ft_strcmp(tab[++(*i)], "-") == 0)
		*line += 1;
	(!ft_check_numbers(tab[(*i)], 1)) ? ft_error(2, *line) : 0;
	t = ft_strsplit(tab[*i], ',');
	(!t[0] || !t[1] || !t[2] || t[3]) ? ft_error(2, *line) : 0;
	rot->x = ft_atoi(t[0]);
	rot->y = ft_atoi(t[1]);
	rot->z = ft_atoi(t[2]);
	while (t[++j])
		free(t[j]);
	free(t);
	while (ft_strcmp(tab[++(*i)], "/orientation") != 0)
		(!ft_strcmp(tab[(*i)], "-")) ? *line += 1 : ft_error(2, *line);
	return (1);
}
