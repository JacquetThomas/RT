/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 15:36:13 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/02/18 18:59:47 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlen(const char *str)
{
	size_t		len;
	unsigned	c;

	len = 0;
	while (1)
	{
		c = *(unsigned *)str;
		if ((c & 0xff) == 0)
			return (len);
		if ((c & 0xff00) == 0)
			return (len + 1);
		if ((c & 0xff0000) == 0)
			return (len + 2);
		if ((c & 0xff000000) == 0)
			return (len + 3);
		len += 4;
		str += 4;
	}
	return (0);
}
