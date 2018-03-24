/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 18:40:40 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/13 15:50:18 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char			**ft_strsplit(char const *str, char c)
{
	size_t	len;
	int		i;
	char	**tab;

	len = 0;
	i = 0;
	if (str == NULL)
		return (NULL);
	if ((tab = (char **)malloc(sizeof(char *) * (ft_countwords(str, c) + 1))))
	{
		while (*str)
		{
			while (*str == c)
				str++;
			if (*str)
			{
				len = ft_getword(str, c);
				tab[i++] = ft_strsub(str, 0, len);
				str += len;
			}
		}
		tab[i] = NULL;
		return (tab);
	}
	return (NULL);
}
