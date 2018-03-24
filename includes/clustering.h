/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clustering.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 19:34:34 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/02/27 15:27:50 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLUSTERING_H
# define CLUSTERING_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <pthread.h>
# include "get_next_line.h"
# include "rt_defines.h"
# include "rt_structures.h"

# define PORT			4242
# define NB_MAX_CLIENT	1199

typedef struct			s_server
{
	struct sockaddr_in	serv_addr;
	struct sockaddr		cli_addr[NB_MAX_CLIENT];
	socklen_t			clilen[NB_MAX_CLIENT];
	long				clisock[NB_MAX_CLIENT];
	long				sockfd;
}						t_server;

typedef struct			s_client
{
	struct sockaddr_in	serv_addr;
	struct hostent		*server;
	long				sockfd;
}						t_client;

typedef struct			s_cluster
{
	int					size_x;
	int					size_y;
	double				rand[MAX_RAND];
	t_cl				cl;
	t_rt				rt;
	uint32_t			*pixels;
}						t_cluster;

typedef struct			s_buffer
{
	void				*data;
	int					next;
	int					size;
}						t_buffer;

void					ft_init_buffer(t_buffer *buff, int size);
void					ft_serialize_int(int i, t_buffer *buff);
void					ft_serialize_double(double d, t_buffer *buff);
void					ft_serialize_uint32t(uint32_t u, t_buffer *buff);
void					ft_serialize_t_color(t_color c, t_buffer *buff);
void					ft_serialize_t_vector(t_vector v, t_buffer *buff);
void					ft_serialize_t_light(t_light l, t_buffer *buff);
void					ft_serialize_t_noise(t_noise n, t_buffer *buff);
void					ft_serialize_t_object(t_object o, t_buffer *buff);
void					ft_serialize_t_eye(t_eye e, t_buffer *buff);
void					ft_serialize_t_config(t_config c, t_buffer *buff);
void					ft_serialize_t_rt(t_rt r, t_buffer *buff);
void					ft_serialize_rand(double rand[MAX_RAND], \
																t_buffer *buff);
int						ft_unserialize_int(int i, t_buffer *buff);
double					ft_unserialize_double(double d, t_buffer *buff);
uint32_t				ft_unserialize_uint32t(uint32_t u, t_buffer *buff);
void					ft_unserialize_t_color(t_color *c, t_buffer *buff);
void					ft_unserialize_t_vector(t_vector *v, t_buffer *buff);
void					ft_unserialize_t_light(t_light *l, t_buffer *buff);
void					ft_unserialize_t_noise(t_noise *n, t_buffer *buff);
void					ft_unserialize_t_object(t_object *o, t_buffer *buff);
void					ft_unserialize_t_eye(t_eye *e, t_buffer *buff);
void					ft_unserialize_t_config(t_config *c, t_buffer *buff);
void					ft_unserialize_t_rt(t_rt *r, t_buffer *buff);
void					ft_unserialize_rand(double rand[MAX_RAND], \
																t_buffer *buff);

#endif
