/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 14:32:13 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/17 19:22:31 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_server(t_server *server)
{
	if ((server->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		errors(ERR_SYS, "Error opening socket.");
	server->serv_addr.sin_family = AF_INET;
	server->serv_addr.sin_addr.s_addr = INADDR_ANY;
	server->serv_addr.sin_port = htons(PORT);
	if (bind(server->sockfd, (struct sockaddr *)&server->serv_addr, \
												sizeof(server->serv_addr)) < 0)
		errors(ERR_SYS, "Error on binding,");
}

void	ft_get_img(t_server server, uint32_t *pixels, int nb_cli)
{
	int			i;
	int			j;
	int			k;
	uint32_t	w[WIN_W * WIN_H];

	i = -1;
	ft_bzero(w, sizeof(w));
	while (++i < nb_cli)
	{
		k = -1;
		while (++k < (WIN_W * WIN_H) / (nb_cli + 1))
			if (recv(server.clisock[i], &w[k], sizeof(uint32_t), 0) == -1)
				errors(ERR_SYS, "Error while receiveing image.");
		j = -(nb_cli - i);
		k = 0;
		while ((j += (nb_cli + 1)) < WIN_W * WIN_H)
		{
			pixels[j] = w[k];
			k++;
		}
	}
}

void	ft_send_data(t_data data, t_server server, int nb_cli, int loop)
{
	int			i;
	t_buffer	buff;

	i = -1;
	ft_init_buffer(&buff, sizeof(t_rt) + (sizeof(double) * MAX_RAND) + \
																sizeof(int));
	while (++i < nb_cli)
	{
		data.rt.offset = i + 1;
		ft_serialize_t_rt(data.rt, &buff);
		ft_serialize_rand(data.rand, &buff);
		ft_serialize_int(loop, &buff);
		if (sendto(server.clisock[i], buff.data, buff.size, 0, \
								&server.cli_addr[i], server.clilen[i]) == -1)
			errors(ERR_SYS, "Error sending data to client.");
		ft_bzero(buff.data, buff.size);
		buff.next = 0;
	}
	free(buff.data);
}

void	main_loop_server(t_data *data, int nb_cli, t_server server)
{
	int		loop;

	loop = 2;
	while (loop)
	{
		if (loop == EVENT_UPDATE)
		{
			if ((data->keys.i == 0 && data->keys.h == 0) || data->keys.r == 1)
			{
				ft_send_data(*data, server, nb_cli, loop);
				cl_run(&data->cl, (size_t[WORK_DIM]){data->sdl.size.y, \
				data->sdl.size.x}, 3, \
				(t_arg){data->sdl.draw_surface->pixels, sizeof(uint32_t) * \
				data->sdl.size.y * data->sdl.size.x, CL_MEM_WRITE_ONLY}, \
				(t_arg){&data->rt, sizeof(t_rt), CL_MEM_READ_ONLY}, \
				(t_arg){&data->rand, MAX_RAND * sizeof(double), \
					CL_MEM_READ_ONLY});
				ft_get_img(server, data->sdl.draw_surface->pixels, nb_cli);
			}
			data->keys.r = 0;
			(data->sdl.show_info) ? update_info(&data->sdl, &data->rt) : 0;
			sdl_run(&data->sdl);
		}
		loop = sdl_events(&data->sdl, &data->keys, &data->rt);
	}
}

void	server(t_data data, int nb_cli)
{
	t_server	sr;
	int			i;

	i = -1;
	data.rt.nb_cli = nb_cli;
	ft_bzero(&sr, sizeof(t_server));
	init_server(&sr);
	while (++i < nb_cli)
	{
		listen(sr.sockfd, 5);
		sr.clilen[i] = sizeof(sr.cli_addr[i]);
		(sr.clisock[i] = accept(sr.sockfd, (struct sockaddr *)&sr.cli_addr[i], \
				&sr.clilen[i])) < 0 ? errors(ERR_SYS, "Error on accept\n") : 0;
	}
	sdl_init(&data.sdl, PROGRAM_NAME);
	loading(&data.sdl);
	data.sdl.filters = 0;
	cl_init(&data.cl, 0);
	main_loop_server(&data, nb_cli, sr);
	cl_end(&data.cl);
	sdl_end(&data.sdl);
	i = -1;
	while (++i < NB_MAX_CLIENT)
		close(sr.clisock[i]);
	close(sr.sockfd);
}
