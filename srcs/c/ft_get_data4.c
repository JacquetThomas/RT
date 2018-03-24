/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:28:40 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/16 18:54:09 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			ft_get_perturbation(char **tab, double *np, int *i, int *line)
{
	while (ft_strcmp(tab[++(*i)], "-") == 0)
		*line += 1;
	(!ft_check_numbers(tab[(*i)], 0)) ? ft_error(2, *line) : 0;
	((*np = ft_atod(tab[(*i)])) < 0) ? ft_error(2, *line - 1) : 0;
	while (ft_strcmp(tab[++(*i)], "/perturbation") != 0)
		(!ft_strcmp(tab[(*i)], "-")) ? *line += 1 : ft_error(2, *line);
	return (1);
}

void		ft_implode(t_parser *p, char *sep, int nb_line)
{
	int		i;
	int		len;

	len = nb_line * ft_strlen(sep);
	i = -1;
	while (++i < nb_line)
		len += ft_strlen(p->tab2[i]);
	i = -1;
	if ((p->data = malloc(len * sizeof(char))) == NULL)
		ft_error(3, 0);
	while (++i < nb_line)
	{
		ft_strcat(p->data, p->tab2[i]);
		if (i + 1 != nb_line)
			ft_strcat(p->data, sep);
	}
	i = -1;
	while (++i < len)
		p->data[i] = ft_tolower(p->data[i]);
	p->data[i] = '\0';
}

int			ft_get_int(int *i, int fd)
{
	char	*line;

	get_next_line(fd, &line);
	*i = ft_atoi(line);
	free(line);
	return (1);
}

int			ft_get_double(double *d, int fd)
{
	char	*line;

	get_next_line(fd, &line);
	*d = ft_atod(line);
	free(line);
	return (1);
}

void		ft_get_data2(char **tab, t_data *data, int *line, int *i)
{
	if (ft_strcmp(tab[*i], "cone") == 0)
		ft_get_cone(tab, data, i, line);
	else if (ft_strcmp(tab[*i], "cube") == 0)
		ft_get_cube(tab, data, i, line);
	else if (!ft_comment(tab[*i]) || !tab[*i + 1])
		ft_error(2, *line);
}
