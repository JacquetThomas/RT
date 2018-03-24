/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 16:15:27 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/17 19:30:50 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

long	ft_error(int error, int line)
{
	if (error == 0)
		ft_putstr("usage: ./rt <fichier>\n");
	else if (error == 1)
		ft_putstr("error: invalid file\n");
	else if (error == 2)
	{
		ft_putstr("invalid scene, error line : ");
		ft_putnbr(line + 1);
		ft_putchar('\n');
	}
	else if (error == 3)
		ft_putstr("malloc error\n");
	else if (error == 4)
		ft_putstr("error, opening socket\n");
	else if (error == 5)
		ft_putstr("error, no such host\n");
	exit(EXIT_FAILURE);
}

long	errors(const int err, const char *comment)
{
	ft_putstr_fd("RT: ", 2);
	if (comment)
	{
		ft_putstr_fd(comment, 2);
		ft_putstr_fd(" ", 2);
	}
	if (err == ERR_SYS)
		ft_putendl_fd(strerror(errno), 2);
	else if (err == ERR_CL)
		ft_putstr_fd("OpenCL failure\n", 2);
	else if (err == ERR_SDL)
		ft_putendl_fd(SDL_GetError(), 2);
	else if (err == ERR_USAGE)
		ft_putendl_fd("\nUsage : ./"PROGRAM_NAME" scene.xml\n", 2);
	exit(EXIT_FAILURE);
	return (0);
}

void	cl_error_log(t_cl *cl, const cl_int error_code)
{
	size_t	size;
	char	*str;

	ft_putstr_fd("error code : ", 2);
	ft_putnbr_fd(error_code, 2);
	ft_putstr_fd("\n", 2);
	clGetProgramBuildInfo(cl->program, cl->device_id, CL_PROGRAM_BUILD_LOG, 0, \
			NULL, &size);
	if ((str = (char *)malloc(size + 1)) == NULL)
		errors(ERR_SYS, "print_build_log malloc error --");
	clGetProgramBuildInfo(cl->program, cl->device_id, CL_PROGRAM_BUILD_LOG, \
			size, str, NULL);
	ft_putchar('\n');
	ft_putendl(str);
	exit(EXIT_FAILURE);
}

void	check_truc(const char **tab, int nb_line)
{
	int		i;
	int		j;
	int		k;
	int		l;

	i = -1;
	while (++i < nb_line)
	{
		j = -1;
		k = 0;
		l = 0;
		while (tab[i][++j])
		{
			(tab[i][j] == '>') ? (k++) : 0;
			(tab[i][j] == '<') ? (l++) : 0;
		}
		(l != k) ? ft_error(2, i) : 0;
	}
}
