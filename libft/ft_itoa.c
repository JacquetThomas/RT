/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:58:42 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/11 19:02:30 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char			*ft_itoa(int n)
{
	char			*str;
	int				i;
	unsigned int	nb;

	nb = 0;
	i = 0;
	if ((str = (char *)malloc(sizeof(char) * (ft_nblen(n) + 1))) == NULL)
		return (NULL);
	if (n < 0)
		nb = (unsigned int)-n;
	else
		nb = (unsigned int)n;
	if (nb == 0)
		str[i] = '0';
	while (nb > 0 || i == 0)
	{
		str[i++] = nb % 10 + 48;
		nb /= 10;
	}
	if (n < 0)
		str[i++] = '-';
	str[i] = '\0';
	ft_strrev(str);
	return (str);
}
