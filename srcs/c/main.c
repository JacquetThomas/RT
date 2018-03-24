/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 14:52:43 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/18 14:26:54 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			ft_limits(double nb, double min, double max)
{
	if (nb < min)
		return (min);
	else if (nb > max)
		return (max);
	else
		return (nb);
}

static void		main_loop(t_data *data)
{
	int			loop;
	int			i;

	i = data->rt.nb_obj;
	loop = 2;
	while (loop)
	{
		if (loop == EVENT_UPDATE)
		{
			if ((data->keys.i == 0 && data->keys.h == 0) || data->keys.r == 1)
				cl_run(&data->cl, (size_t[WORK_DIM]){data->sdl.size.y, \
				data->sdl.size.x}, 3, (t_arg){data->sdl.draw_surface->pixels, \
				sizeof(uint32_t) * data->sdl.size.y * data->sdl.size.x, \
				CL_MEM_WRITE_ONLY}, (t_arg){&data->rt, sizeof(t_rt), \
				CL_MEM_READ_ONLY}, (t_arg){&data->rand, MAX_RAND * \
				sizeof(double), CL_MEM_READ_ONLY});
			data->keys.r = 0;
			(data->sdl.show_info) ? update_info(&data->sdl, &data->rt) : 0;
			sdl_run(&data->sdl);
		}
		loop = sdl_events(&data->sdl, &data->keys, &data->rt);
		data->keys.p = (data->keys.p) ? save_picture(&data->sdl) : 0;
	}
}

void			ft_server(t_data data, char *file, int nb_cli)
{
	if (nb_cli <= 0 || nb_cli > NB_MAX_CLIENT)
		errors(ERR_SYS, "invalid number of clients\n");
	ft_init_struct(&data);
	ft_parse(file, &data);
	ft_init_data(&data);
	ft_get_conf(&data.rt.config, file);
	if (data.rt.config.focus_dist != 0)
		ft_get_focus(&data.rt.config.focus, data.rt.eye, &data.rt);
	else
		data.rt.config.dof = 0;
	data.sdl.size.x = WIN_W;
	data.sdl.size.y = WIN_H;
	server(data, nb_cli);
}

void			start(t_data data, char *file)
{
	ft_init_struct(&data);
	ft_parse(file, &data);
	ft_init_data(&data);
	ft_get_conf(&data.rt.config, file);
	if (data.rt.config.focus_dist != 0)
		ft_get_focus(&data.rt.config.focus, data.rt.eye, &data.rt);
	else
		data.rt.config.dof = 0;
	sdl_init(&data.sdl, PROGRAM_NAME);
	loading(&data.sdl);
	data.sdl.filters = 0;
	cl_init(&data.cl, 0);
	main_loop(&data);
	cl_end(&data.cl);
	sdl_end(&data.sdl);
}

int				main(int ac, char **av)
{
	t_data		data;

	ft_bzero(&data, sizeof(t_data));
	if (ac < 2)
		ft_error(0, 0);
	else if (av[1] == NULL)
		ft_error(1, 0);
	if (ac >= 3 && ft_strcmp(av[1], "--client") == 0)
		client(init_client(av[2]));
	else if (ac == 4 && ft_strcmp(av[2], "--server") == 0)
		ft_server(data, av[1], ft_atoi(av[3]));
	else
		start(data, av[1]);
	return (0);
}
