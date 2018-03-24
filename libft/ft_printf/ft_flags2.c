/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:53:04 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/02/18 14:50:51 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_isflag(char c)
{
	char	*flags;
	int		i;
	int		l;

	l = (int)ft_strlen(FLAGS);
	i = 0;
	if (!(flags = ft_strnew(l)))
		exit(-1);
	flags = ft_strcpy(flags, FLAGS);
	while (flags[i])
	{
		if (c == flags[i])
		{
			ft_bzero(flags, l);
			free(flags);
			return (1);
		}
		i++;
	}
	ft_bzero(flags, l);
	free(flags);
	return (0);
}

int			ft_validflags(t_print *p)
{
	char	*s;
	int		l;

	l = 0;
	s = p->flags;
	while (s[l])
	{
		if (s[l] != 32 && s[l] != 35 && s[l] != 43 && s[l] != 45 && s[l] != 48)
			if (s[l] != 104 && s[l] != 106 && s[l] != 108 && s[l] != 122)
				if (s[l] != 46 && (s[l] > 57 || s[l] < 48))
					if (!ft_isflag(s[l]))
					{
						p->conv = s[l];
						s[l + 1] = '\0';
						return (0);
					}
		l++;
	}
	return (1);
}
