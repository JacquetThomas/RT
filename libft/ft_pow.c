/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 19:20:10 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/02/20 18:06:09 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_pow(int n, int power)
{
	int		i;
	int		nb;

	nb = n;
	i = 1;
	if (power == 0)
		return (1);
	while (++i <= power)
		nb *= n;
	return (nb);
}
