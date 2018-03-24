/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 16:42:48 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/12/04 15:47:21 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int nb;
	int neg;

	neg = 1;
	nb = 0;
	while (*str <= 32 && *str >= 0 && *str != '\a' && *str != '\e')
		str++;
	if (ft_strcmp(str, "-2147483648") == 0)
		return (-2147483648);
	if (*str < 48 || *str > 57)
	{
		if (*str == '-')
			neg = -1;
		else if (*str != '+')
			return (0);
		str++;
	}
	if (*str < 48 || *str > 57)
		return (-1);
	while (*str <= 57 && *str >= 48)
		nb = nb * 10 + *str++ - 48;
	return (nb * neg);
}
