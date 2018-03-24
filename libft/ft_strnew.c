/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:09:45 by bmoiroud          #+#    #+#             */
/*   Updated: 2016/11/22 16:17:16 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*s;

	i = 0;
	if ((s = (char *)malloc((size + 1) * sizeof(char))) != NULL)
	{
		while (i <= size)
		{
			s[i] = '\0';
			i++;
		}
		return (s);
	}
	return (NULL);
}
