/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 13:57:17 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/01/05 16:03:38 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_freeall(char *tmp, char **buff, char **line, int ret)
{
	tmp = NULL;
	if (ret == -1)
		return (-1);
	if (*buff == NULL)
		return (0);
	if (ft_strlen(*buff) == 0)
	{
		free(*buff);
		*buff = NULL;
		return (0);
	}
	*line = ft_strdup(*buff);
	free(*buff);
	*buff = NULL;
	return (1);
}

static int		ft_checkbuff(char **buff, char **line)
{
	char	*tmp;

	if ((tmp = ft_strchr(*buff, '\n')))
	{
		*tmp = '\0';
		*line = ft_strdup(*buff);
		tmp++;
		*buff = ft_strdup(tmp);
		tmp = NULL;
		return (1);
	}
	return (0);
}

static int		ft_checkread(char *tmp, char **buff, char **line)
{
	char	*tmp2;

	if ((tmp2 = ft_strchr(tmp, '\n')))
	{
		*tmp2 = '\0';
		*line = ft_strjoin(*buff, tmp);
		free(*buff);
		tmp2++;
		*buff = ft_strdup(tmp2);
		tmp2 = NULL;
		return (1);
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static char		*buff = NULL;
	char			tmp[BUFF_SIZE + 1];
	char			*tmp2;
	int				ret;

	ret = 0;
	if (buff == NULL)
		buff = ft_strnew(0);
	if (fd < 0 || line == NULL)
		return (-1);
	if (buff != NULL)
		if (ft_checkbuff(&buff, line) != 0)
			return (1);
	while ((ret = read(fd, tmp, BUFF_SIZE)) != 0)
	{
		if (ret == -1)
			return (-1);
		tmp[ret] = '\0';
		if (ft_checkread(tmp, &buff, line) != 0)
			return (1);
		tmp2 = buff;
		buff = ft_strjoin(buff, tmp);
		free(tmp2);
	}
	return (ft_freeall(tmp, &buff, line, ret));
}
