/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:28:01 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/13 15:28:12 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_get_intensity(char **tab, double *intensity, int *i, int *line)
{
	while (ft_strcmp(tab[++(*i)], "-") == 0)
		*line += 1;
	(!ft_check_numbers(tab[(*i)], 0)) ? ft_error(2, *line) : 0;
	*intensity = ft_atoi(tab[(*i)]);
	(*intensity < 0) ? ft_error(2, *line) : 0;
	while (ft_strcmp(tab[++(*i)], "/intensity") != 0)
		(!ft_strcmp(tab[(*i)], "-")) ? *line += 1 : ft_error(2, *line);
	return (1);
}

int		ft_get_reflection(char **tab, double *ref, int *i, int *line)
{
	while (ft_strcmp(tab[++(*i)], "-") == 0)
		*line += 1;
	(!ft_check_numbers(tab[(*i)], 0)) ? ft_error(2, *line) : 0;
	*ref = ft_atod(tab[(*i)]);
	(*ref < 0 || *ref > 100) ? ft_error(2, *line) : 0;
	while (ft_strcmp(tab[++(*i)], "/reflection") != 0)
		(!ft_strcmp(tab[(*i)], "-")) ? *line += 1 : ft_error(2, *line);
	return (1);
}

int		ft_get_bm(char **tab, double *bm, int *i, int *line)
{
	while (ft_strcmp(tab[++(*i)], "-") == 0)
		*line += 1;
	(!ft_check_numbers(tab[(*i)], 0)) ? ft_error(2, *line) : 0;
	*bm = ft_atod(tab[(*i)]);
	while (ft_strcmp(tab[++(*i)], "/bump_mapping") != 0)
		(!ft_strcmp(tab[(*i)], "-")) ? *line += 1 : ft_error(2, *line);
	return (1);
}

int		ft_get_opacity(char **tab, double *transp, int *i, int *line)
{
	while (ft_strcmp(tab[++(*i)], "-") == 0)
		*line += 1;
	(!ft_check_numbers(tab[(*i)], 0)) ? ft_error(2, *line) : 0;
	*transp = 100.0 - ft_atod(tab[(*i)]);
	(*transp > 100 || *transp < 0) ? ft_error(2, *line) : 0;
	while (ft_strcmp(tab[++(*i)], "/opacity") != 0)
		(!ft_strcmp(tab[(*i)], "-")) ? *line += 1 : ft_error(2, *line);
	return (1);
}

int		ft_get_specularity(char **tab, double *spec, int *i, int *line)
{
	while (ft_strcmp(tab[++(*i)], "-") == 0)
		*line += 1;
	(!ft_check_numbers(tab[(*i)], 0)) ? ft_error(2, *line) : 0;
	*spec = ft_atod(tab[(*i)]);
	while (ft_strcmp(tab[++(*i)], "/specularity") != 0)
		(!ft_strcmp(tab[(*i)], "-")) ? *line += 1 : ft_error(2, *line);
	return (1);
}
