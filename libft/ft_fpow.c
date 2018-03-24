/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fpow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 16:55:56 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/03/20 16:56:21 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_fpow(double n, int power)
{
	int		i;
	double	nb;

	nb = n;
	i = 1;
	if (power == 0)
		return (1);
	while (++i <= power)
		nb *= n;
	return (nb);
}
