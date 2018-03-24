/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:30:52 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/02/17 15:57:26 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strnjoin(char *s1, char *s2, int n)
{
	char	*s3;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(s2);
	j = -1;
	i = -1;
	s3 = NULL;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (len > n)
		len = n;
	if ((s3 = malloc(((ft_strlen(s1) + len + 1) * sizeof(char)))) == NULL)
		return (NULL);
	while (s1[i++])
		s3[i] = s1[i];
	while (s2[j++] && j < n)
	{
		s3[i] = s2[j];
		i++;
	}
	s3[i] = '\0';
	return (s3);
}
