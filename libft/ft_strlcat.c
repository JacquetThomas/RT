/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:32:16 by bmoiroud          #+#    #+#             */
/*   Updated: 2016/11/24 16:48:26 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_l(const char *s, size_t size)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && i < size)
	{
		i++;
	}
	return (i);
}

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dstlen;

	dstlen = ft_strlen_l(dst, size);
	i = 0;
	while (src[i] && (i + dstlen + 1) < size)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	if (dstlen - size > 0)
		dst[dstlen + i] = '\0';
	return (dstlen + ft_strlen(src));
}
