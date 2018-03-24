/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 22:29:13 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/13 15:28:50 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_get_texture(char **tab, t_object *obj, int *i, int *line)
{
	while (ft_strcmp(tab[++(*i)], "-") == 0)
		*line += 1;
	if (ft_strcmp(tab[*i], "chessboard") == 0)
		obj->p_texture = CHESSBOARD;
	else if (ft_strcmp(tab[*i], "bricks") == 0)
		obj->p_texture = BRICKS;
	else if (ft_strcmp(tab[*i], "wood") == 0)
		obj->p_texture = WOOD;
	else if (ft_strcmp(tab[*i], "marble") == 0)
		obj->p_texture = MARBLE;
	else
		ft_error(2, *line);
	while (ft_strcmp(tab[++(*i)], "/texture") != 0)
		(!ft_strcmp(tab[(*i)], "-")) ? *line += 1 : ft_error(2, *line);
	return (1);
}

int		ft_get_noise(char **tab, t_noise *noise, int *i, int *line)
{
	char	**t;
	int		j;

	j = -1;
	while (ft_strcmp(tab[++(*i)], "-") == 0)
		*line += 1;
	t = ft_strsplit(tab[*i], ',');
	(!t[0] || !t[1] || !t[2] || t[3]) ? ft_error(2, *line) : 0;
	((noise->oct = ft_atod(t[0])) <= 0) ? ft_error(2, *line) : 0;
	noise->freq = ft_atod(t[1]);
	((noise->persis = ft_atod(t[2])) <= 0) ? ft_error(2, *line) : 0;
	while (t[++j])
		free(t[j]);
	free(t);
	while (ft_strcmp(tab[++(*i)], "/noise") != 0)
		(!ft_strcmp(tab[(*i)], "-")) ? *line += 1 : ft_error(2, *line);
	return (1);
}

int		ft_comment(char *str)
{
	if (ft_strncmp(str, "!--", 3) == 0 && \
						ft_strncmp(str + (ft_strlen(str) - 2), "--", 2) == 0)
		return (1);
	return (0);
}

int		ft_translation(char **tab, t_vector *pos, int *i, int *line)
{
	t_vector	pos2;
	char		**t;
	int			j;

	j = -1;
	while (ft_strcmp(tab[++(*i)], "-") == 0)
		*line += 1;
	(!ft_check_numbers(tab[(*i)], 1)) ? ft_error(2, *line) : 0;
	t = ft_strsplit(tab[*i], ',');
	(!t[0] || !t[1] || !t[2] || t[3]) ? ft_error(2, *line) : 0;
	pos2.x = ft_atod(t[0]);
	pos2.y = ft_atod(t[1]);
	pos2.z = ft_atod(t[2]);
	while (t[++j])
		free(t[j]);
	free(t);
	*pos = ft_add_vector(*pos, pos2);
	while (ft_strcmp(tab[++(*i)], "/translation") != 0)
		(!ft_strcmp(tab[(*i)], "-")) ? *line += 1 : ft_error(2, *line);
	return (1);
}

int		ft_get_negative(char **tab, int *neg, int *i, int *line)
{
	while (ft_strcmp(tab[++(*i)], "-") == 0)
		*line += 1;
	if (!ft_check_numbers(tab[(*i)], 0))
		ft_error(2, *line);
	*neg = ft_atoi(tab[(*i)]);
	if (*neg < 0 || *neg > 1)
		ft_error(2, *line);
	(*neg < 0 || *neg > 1) ? ft_error(2, *line) : 0;
	while (ft_strcmp(tab[++(*i)], "/negative") != 0)
		(!ft_strcmp(tab[(*i)], "-")) ? *line += 1 : ft_error(2, *line);
	return (1);
}
