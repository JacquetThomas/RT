/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_objects2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:45:06 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/10 17:48:34 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_get_object2(char **tab, t_rt *rt, int *i, int j[12])
{
	int		k;

	k = rt->nb_obj;
	if (ft_strcmp(tab[(*i)], "translation") == 0 && j[0])
		ft_translation(tab, &rt->objects[k].pos, i, &rt->line);
	else if (ft_strcmp(tab[(*i)], "noise") == 0 && !j[10])
		j[10] = ft_get_noise(tab, &rt->objects[k].noise, i, &rt->line);
	else if (ft_strcmp(tab[(*i)], "bump_mapping") == 0 && !j[11])
		j[11] = ft_get_bm(tab, &rt->objects[k].bm, i, &rt->line);
	else if (!ft_comment(tab[(*i)]) && ft_strcmp(tab[(*i)], "-") != 0)
		ft_error(2, rt->line);
}

void	ft_get_object(char **tab, t_rt *rt, int *i, int j[12])
{
	int		k;

	k = rt->nb_obj;
	if (ft_strcmp(tab[(*i)], "position") == 0 && !j[0])
		j[0] = ft_get_coord(tab, &rt->objects[k].pos, i, &rt->line);
	else if (ft_strcmp(tab[(*i)], "size") == 0 && !j[1])
		j[1] = ft_get_size(tab, &rt->objects[k].size, i, &rt->line);
	else if (ft_strcmp(tab[(*i)], "reflection") == 0 && !j[2])
		j[2] = ft_get_reflection(tab, &rt->objects[k].reflect, i, &rt->line);
	else if (ft_strcmp(tab[(*i)], "negative") == 0 && !j[3])
		j[3] = ft_get_negative(tab, &rt->objects[k].negative, i, &rt->line);
	else if (ft_strcmp(tab[(*i)], "opacity") == 0 && !j[4])
		j[4] = ft_get_opacity(tab, &rt->objects[k].transp, i, &rt->line);
	else if (ft_strcmp(tab[(*i)], "specularity") == 0 && !j[5])
		j[5] = ft_get_specularity(tab, &rt->objects[k].spec, i, &rt->line);
	else if (ft_strcmp(tab[(*i)], "perturbation") == 0 && !j[6])
		j[6] = ft_get_perturbation(tab, &rt->objects[k].np, i, &rt->line);
	else if (ft_strcmp(tab[(*i)], "texture") == 0 && !j[7])
		j[7] = ft_get_texture(tab, &rt->objects[k], i, &rt->line);
	else if (ft_strcmp(tab[(*i)], "color") == 0 && !j[8])
		j[8] = ft_get_color(tab, &rt->objects[k].color, i, &rt->line);
	else if (ft_strcmp(tab[(*i)], "orientation") == 0 && !j[9])
		j[9] = ft_get_rotation(tab, &rt->objects[k].rot, i, &rt->line);
	else
		ft_get_object2(tab, rt, i, j);
}
