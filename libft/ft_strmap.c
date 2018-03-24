/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:34:46 by bmoiroud          #+#    #+#             */
/*   Updated: 2016/11/12 18:51:51 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(const char *s, char (*f)(char))
{
	char	*s2;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((s2 = (char *)malloc((ft_strlen(s) + 1) * sizeof(char))) == NULL)
		return (NULL);
	while (s[i])
	{
		s2[i] = (*f)(s[i]);
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
