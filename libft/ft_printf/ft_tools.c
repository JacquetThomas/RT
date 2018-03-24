/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 19:17:43 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/02/18 14:50:51 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_pow(int nb, int power)
{
	int		ret;

	power++;
	ret = nb;
	while (power != 0)
	{
		ret *= power;
		power--;
	}
	return (ret);
}

char		*ft_getnbr(char *str)
{
	char	*nbr;
	int		i;

	i = 0;
	if (!(nbr = ft_strnew(13)))
		exit(-1);
	while (str[i] >= 48 && str[i] <= 57)
	{
		ft_strncat(nbr, str + i, 1);
		i++;
	}
	return (nbr);
}

t_print		*ft_reset(t_print *p)
{
	ft_bzero(p->lmod, 3);
	p->conv = 0;
	p->hash = 0;
	p->zero = 0;
	p->leftalign = 0;
	p->fieldwidth = 0;
	p->sign = 0;
	p->precision = -1;
	p->nlen = 0;
	p->plen = 0;
	p->len = 0;
	return (p);
}

t_print		ft_init(t_print *new)
{
	ft_bzero(new->buff, BUFF_SIZE);
	ft_bzero(new->lmod, 3);
	if (!(new->flags = ft_strnew(0)))
		exit(-1);
	new->bufflen = 0;
	new->hash = 0;
	new->zero = 0;
	new->leftalign = 0;
	new->fieldwidth = 0;
	new->sign = 0;
	new->precision = -1;
	new->ret = 0;
	new->nlen = 0;
	new->plen = 0;
	new->len = 0;
	return (*new);
}

int			ft_nblen(int nb)
{
	int		i;

	i = 0;
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i + 1);
}
