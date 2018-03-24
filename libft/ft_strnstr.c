/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 14:53:40 by bmoiroud          #+#    #+#             */
/*   Updated: 2016/11/14 17:18:14 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	lens2;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	lens2 = ft_strlen(s2);
	if (lens2 == 0)
		return ((char *)s1);
	while (s1[i] && n >= lens2)
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while (s1[i + j] == s2[j] && s2[j] && s1[i + j])
				j++;
			if (s2[j] == '\0')
				return ((char *)s1 + i);
		}
		i++;
		n--;
	}
	return (NULL);
}
