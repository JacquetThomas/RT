/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 15:47:38 by bmoiroud          #+#    #+#             */
/*   Updated: 2016/11/13 16:03:07 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char *dest;

	if (n > 0)
	{
		dest = (unsigned char *)s;
		while (n > 0)
		{
			dest[n - 1] = '\0';
			n--;
		}
	}
}
