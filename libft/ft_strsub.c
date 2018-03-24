/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:11:53 by bmoiroud          #+#    #+#             */
/*   Updated: 2016/11/21 18:03:09 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *str, unsigned int start, size_t len)
{
	char	*str2;
	size_t	i;

	i = 0;
	str2 = NULL;
	if (str == NULL)
		return (NULL);
	if ((str2 = (char *)malloc((len + 1) * sizeof(char))) == NULL)
		return (NULL);
	while (i < len)
	{
		str2[i] = str[start + i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}
