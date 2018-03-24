/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:33:59 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/12/08 14:28:46 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

static unsigned int		ft_rand(const unsigned int x)
{
	unsigned int	value;

	value = ((x ^ 61) ^ (x >> 16)) * 9;
	value = value ^ (value << 4);
	value *= 668265261;
	return (value ^ (value >> 15));
}

static unsigned int		ft_rand2(const unsigned int x, const unsigned int y)
{
	unsigned int	value = ft_rand(x);

	return (ft_rand(value ^ y));
}

static unsigned int		ft_rand3(const unsigned int x, const unsigned int y, const unsigned int z)
{
	unsigned int	value = ft_rand(x);

	value = ft_rand(value ^ y);
	return (ft_rand(value ^ z));
}