/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 19:41:11 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/02/16 17:36:50 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_atoi_base(char *str, int base)
{
	int		nb;
	int		neg;
	int		i;

	i = 0;
	neg = 1;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '-')
			neg = -1;
		else
		{
			if (str[i] >= 48 && str[i] <= 57)
				nb += str[i] - 48;
			else if (str[i] >= 65 && str[i] <= 90)
				nb += str[i] - 55;
			else if (str[i] >= 97 && str[i] <= 122)
				nb += str[i] - 87;
		}
		nb *= (str[i + 1]) ? ft_pow(base, i) : 1;
		str++;
	}
	return (nb * neg);
}
