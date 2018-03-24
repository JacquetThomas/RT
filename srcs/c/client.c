/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 16:04:15 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/02/27 15:04:16 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_client	init_client(char *host)
{
	t_client	client;
	int			ret;

	ret = 0;
	ft_bzero(&client, sizeof(t_client));
	client.sockfd = socket(AF_INET, SOCK_STREAM, 0);
	(client.sockfd < 0) ? errors(ERR_SYS, "Error, opening socket.") : 0;
	client.server = gethostbyname(host);
	(client.server == NULL) ? errors(ERR_SYS, "Error, no such host.") : 0;
	ft_bzero((char *)&client.serv_addr, sizeof(client.serv_addr));
	client.serv_addr.sin_family = AF_INET;
	ft_strncpy((char *)&client.serv_addr.sin_addr.s_addr, \
						(char *)client.server->h_addr, client.server->h_length);
	client.serv_addr.sin_port = htons(PORT);
	ret = connect(client.sockfd, (struct sockaddr *)&client.serv_addr, \
													sizeof(client.serv_addr));
	(ret < 0) ? errors(ERR_SYS, "Error connecting.") : 0;
	return (client);
}

void		ft_receive_data(t_cluster *cluster, int *loop, long sockfd)
{
	t_buffer	buff;
	int			i;

	i = -1;
	ft_bzero(&buff, sizeof(buff));
	ft_init_buffer(&buff, sizeof(t_rt) + (sizeof(double) * MAX_RAND) + \
																sizeof(int));
	while (++i < buff.size)
		if (recv(sockfd, &buff.data[i], 1, 0) == -1)
			errors(ERR_SYS, "Error receiving data.");
	ft_unserialize_t_rt(&cluster->rt, &buff);
	ft_unserialize_rand(cluster->rand, &buff);
	*loop = ft_unserialize_int(*loop, &buff);
	free(buff.data);
}

void		ft_client_loop(t_cluster cluster, t_client client, int loop)
{
	int			i;

	i = -1;
	while (loop)
	{
		if (loop == EVENT_UPDATE)
		{
			cl_run(&cluster.cl, (size_t[WORK_DIM]){cluster.size_y, \
				cluster.size_x}, 3, (t_arg){cluster.pixels, sizeof(uint32_t) * \
				cluster.size_y * cluster.size_x, CL_MEM_WRITE_ONLY}, \
				(t_arg){&cluster.rt, sizeof(t_rt), CL_MEM_READ_ONLY}, \
				(t_arg){&cluster.rand, MAX_RAND * sizeof(double), \
				CL_MEM_READ_ONLY});
			i = -1;
			while (cluster.pixels[++i])
				if (send(client.sockfd, &cluster.pixels[i], \
													sizeof(uint32_t), 0) == -1)
					errors(ERR_SYS, "Error sending image.");
		}
		ft_receive_data(&cluster, &loop, client.sockfd);
	}
}

void		client(t_client client)
{
	t_cluster	cluster;
	t_buffer	buff;
	int			loop;

	ft_bzero(&buff, sizeof(t_buffer));
	ft_bzero(&cluster, sizeof(t_cluster));
	ft_receive_data(&cluster, &loop, client.sockfd);
	(loop != 2) ? errors(-1, "Invalid data received.") : 0;
	cluster.size_x = WIN_W;
	cluster.size_y = WIN_H;
	ft_init_buffer(&buff, BPP * cluster.size_y * cluster.size_x);
	if (!(cluster.pixels = ft_memalloc(BPP * cluster.size_x * cluster.size_y)))
		errors(ERR_SYS, 0);
	cl_init(&cluster.cl, 0);
	ft_client_loop(cluster, client, loop);
	free(cluster.pixels);
	close(client.sockfd);
	cl_end(&cluster.cl);
}
