/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 19:41:06 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/02/18 14:50:51 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_getnblen(intmax_t nb, int base)
{
	int		len;

	len = 0;
	if (nb < 0)
		len++;
	while (nb != 0)
	{
		nb /= base;
		len++;
	}
	return (len);
}

char	*ft_itoa_base_neg(uintmax_t n, int base, unsigned long len)
{
	char			*nbr;
	unsigned long	i;

	i = 0;
	len *= 2;
	if (!(nbr = ft_strnew(len)))
		exit(-1);
	if (n == 0)
		return ("0");
	while (i < len && n != 0)
	{
		nbr[i] = n % base + ((n % base < 10) ? 48 : 55);
		n = ((n >= (uintmax_t)base) ? n / base : 0);
		i++;
	}
	return (ft_strrev(nbr));
}

char	*ft_itoa_base(intmax_t n, int base, unsigned long l)
{
	char		*nbr;
	uintmax_t	nb;
	int			i;

	nb = 0;
	if (n == 0)
		return ("0");
	if (base == 10 || n >= 0)
	{
		i = ft_getnblen(n, base);
		if (!(nbr = ft_strnew(i)))
			exit(-1);
		nb = (n < 0) ? -n : n;
		nbr[0] = (n < 0) ? '-' : nbr[0];
		while (i > 0 && nb != 0)
		{
			nbr[i - 1] = nb % base + ((nb % base < 10) ? 48 : 55);
			nb = ((nb >= (uintmax_t)base) ? nb / base : 0);
			i--;
		}
	}
	else
		return (ft_itoa_base_neg(n, base, l));
	return (nbr);
}
