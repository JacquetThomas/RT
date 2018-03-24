/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:30:52 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/02/17 15:57:38 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoinc(const char *s1, const char *s2, char c)
{
	char	*s3;
	int		i;
	int		j;
	int		len;

	len = (int)ft_strlen(s2);
	j = -1;
	i = -1;
	s3 = NULL;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if ((s3 = malloc(((ft_strlen(s1) + len + 1) * sizeof(char)))) == NULL)
		return (NULL);
	while (s1[i++])
		s3[i] = s1[i];
	while (s2[j++] && s2[j] != c)
	{
		s3[i] = s2[j];
		i++;
	}
	s3[i] = '\0';
	return (s3);
}
