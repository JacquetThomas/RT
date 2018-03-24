/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 18:33:56 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/17 19:01:52 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_get_light(char **t, t_data *data, int *i, int *line)
{
	int		j[2];
	int		k;

	k = data->rt.nb_light;
	ft_bzero(&j, sizeof(j));
	while (ft_strcmp(t[++(*i)], "/light") != 0)
	{
		if (ft_strcmp(t[(*i)], "-") == 0)
			*line += 1;
		else if (ft_strcmp(t[(*i)], "position") == 0 && !j[0])
			j[0] = ft_get_coord(t, &data->rt.lights[k].pos, i, line);
		else if (ft_strcmp(t[(*i)], "intensity") == 0 && !j[1])
			j[1] = ft_get_intensity(t, &data->rt.lights[k].intensity, i, line);
		else if (ft_strcmp(t[(*i)], "translation") == 0 && j[0])
			ft_translation(t, &data->rt.lights[k].pos, i, line);
		else if (!ft_comment(t[(*i)]))
			ft_error(2, *line);
	}
	if (j[0] == 0)
	{
		ft_putstr("light position not set, ");
		ft_error(2, *line);
	}
	data->rt.nb_light++;
}

int		ft_get_camera(char **tab, t_eye *eye, int *i, int *line)
{
	int		j[2];

	ft_bzero(&j, sizeof(j));
	while (ft_strcmp(tab[++(*i)], "/camera") != 0)
	{
		if (ft_strcmp(tab[(*i)], "-") == 0)
			*line += 1;
		else if (ft_strcmp(tab[(*i)], "position") == 0 && !j[0])
			j[0] = ft_get_coord(tab, &eye->pos, i, line);
		else if (ft_strcmp(tab[(*i)], "orientation") == 0 && !j[1])
			j[1] = ft_get_rotation(tab, &eye->rot, i, line);
		else if (ft_strcmp(tab[(*i)], "translation") == 0 && j[0])
			ft_translation(tab, &eye->pos, i, line);
		else if (!ft_comment(tab[(*i)]))
			ft_error(2, *line);
		if (j[1] && eye->rot.x == 0 && eye->rot.y == 0 && eye->rot.z == 0)
			ft_error(2, *line);
	}
	if (j[0] == 0)
	{
		ft_putstr("camera position not set, ");
		ft_error(2, *line);
	}
	return (1);
}

void	ft_get_data(char **tab, t_data *data, int line, int i)
{
	int		j;

	j = 0;
	while (ft_strcmp(tab[++i], "-") == 0 || ft_comment(tab[i]))
		line++;
	(i == 0) ? 0 : (line -= (i / 2));
	(ft_strcmp(tab[i], "scene") != 0) ? ft_error(2, line) : 0;
	while (tab[++i] && ft_strcmp(tab[i], "/scene") != 0)
		if (ft_strcmp(tab[i], "-") == 0)
			line++;
		else if (ft_strcmp(tab[i], "camera") == 0 && j == 0)
			j = ft_get_camera(tab, &data->rt.eye, &i, &line);
		else if (ft_strcmp(tab[i], "light") == 0)
			ft_get_light(tab, data, &i, &line);
		else if (ft_strcmp(tab[i], "cylinder") == 0)
			ft_get_cylinder(tab, data, &i, &line);
		else if (ft_strcmp(tab[i], "sphere") == 0)
			ft_get_sphere(tab, data, &i, &line);
		else if (ft_strcmp(tab[i], "plane") == 0)
			ft_get_plane(tab, data, &i, &line);
		else
			ft_get_data2(tab, data, &line, &i);
	(!tab[i]) ? ft_error(2, line) : 0;
}

void	ft_parse(char *file, t_data *data)
{
	t_parser	p;
	int			i;

	i = -1;
	ft_bzero(&p, sizeof(p));
	ft_get_scene(file, &p);
	ft_clean_tab(&p);
	ft_implode(&p, " - ", p.nb_line);
	p.tab = ft_strsplit(p.data, ' ');
	ft_get_data(p.tab, data, data->rt.line, -1);
	ft_default_value(data->rt.objects, &data->rt);
	while (p.tab[++i])
		free(p.tab[i]);
	free(p.tab);
	i = -1;
	while (++i < p.nb_line)
		free(p.tab2[i]);
	free(p.tab2);
	free(p.data);
}
