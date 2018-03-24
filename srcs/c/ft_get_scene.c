/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:24:01 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/17 19:21:07 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_srch_char(char c, char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (0);
}

int		ft_is_random_stuff(char *line)
{
	int		i;

	i = 0;
	while (++i < 31)
	{
		if (i == 10 || i == ' ' || i == 9)
			i++;
		if (ft_srch_char(i, line))
			return (1);
	}
	return (0);
}

void	ft_get_scene(char *file, t_parser *p)
{
	char	*line;
	int		ret;
	int		fd;
	int		i;

	if (ft_strncmp(ft_strrev(file), "lmx.", 4) != 0)
		ft_error(1, 0);
	ft_strrev(file);
	((fd = open(file, O_RDONLY)) <= 0) ? ft_error(1, 0) : 0;
	while ((ret = get_next_line(fd, &line)) && ++p->nb_line)
	{
		(ret == -1) ? ft_error(1, 0) : 0;
		(ft_is_random_stuff(line)) ? ft_error(1, 0) : 0;
		free(line);
	}
	(ret == 0 && p->nb_line == 0) ? ft_error(1, 0) : 0;
	close(fd);
	if ((p->tab = malloc((p->nb_line) * sizeof(char *))) == NULL)
		ft_error(3, 0);
	fd = open(file, O_RDONLY);
	i = -1;
	while ((ret = get_next_line(fd, &p->tab[++i])))
		(ret == -1) ? ft_error(1, 0) : 0;
	check_truc((const char**)p->tab, p->nb_line);
	close(fd);
}

void	ft_del_char(char *str, char c1, char c2, char c3)
{
	int		i;
	int		len;
	char	*tmp;

	len = ft_strlen(str);
	i = 0;
	(str[0] == c1 || str[0] == c2 || str[0] == c3) ? str[0] = ' ' : 0;
	(str[len - 1] == c1 || str[len - 1] == c2 || str[len - 1] == c3) ? \
														str[len - 1] = ' ' : 0;
	tmp = ft_strtrim(str);
	if (!ft_comment(tmp))
	{
		while (++i < len)
			if (str[i] == c1 || str[i] == c2 || str[i] == c3)
				str[i] = ' ';
	}
	else
	{
		while (++i < len)
			if (str[i] == ' ')
				str[i] = '-';
	}
	free(tmp);
}

void	ft_clean_tab(t_parser *p)
{
	int		i;
	char	*tmp;

	i = -1;
	if ((p->tab2 = malloc((p->nb_line) * sizeof(char *))) == NULL)
		ft_error(3, 0);
	while (++i < p->nb_line)
	{
		tmp = ft_strtrim(p->tab[i]);
		(ft_strlen(tmp) > 0) ? ft_del_char(tmp, '<', '>', '\t') : 0;
		p->tab2[i] = ft_strtrim(tmp);
		free(tmp);
	}
	i = -1;
	while (++i < p->nb_line)
		free(p->tab[i]);
	free(p->tab);
}
