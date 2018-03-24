/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 15:07:34 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/12 15:54:42 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_init_data(t_data *data)
{
	t_rt	*rt;
	int		i;

	i = -1;
	rt = &data->rt;
	while (++i < rt->nb_obj)
		rt->objects[i].rot = ft_norm_vector(rt->objects[i].rot);
	i = -1;
	while (++i < MAX_RAND)
		data->rand[i] = (double)rand() / (double)RAND_MAX;
	ft_calc_dir_vec(&data->rt.eye, data->rt.m);
	data->sdl.size.x = WIN_W;
	data->sdl.size.y = WIN_H;
	data->rt.config.lights = 1;
}

void	ft_init_struct(t_data *data)
{
	int		i;

	i = -1;
	ft_bzero(data, sizeof(t_data));
	while (++i < OBJS_MAX)
	{
		data->rt.objects[i].reflect = 0.0;
		data->rt.objects[i].refract = 0.0;
		data->rt.objects[i].transp = 0.0;
		data->rt.objects[i].spec = 1.0;
		data->rt.objects[i].color.c = -1;
	}
	i = -1;
	while (++i < LGTS_MAX)
		data->rt.lights[i].intensity = -1;
}
