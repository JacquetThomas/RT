/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:56:21 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/02/18 14:39:48 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print		*ft_int_flag(t_print *p, char *nbr, int sign, int i)
{
	int		pr;
	int		fw;

	fw = p->fieldwidth;
	pr = p->precision;
	if (p->zero == 1 && p->leftalign != 1 && (pr == -1 || nbr[0] == '-'))
		while (i++ < fw - p->nlen + ((p->sign == 0 || nbr[0] == '-') ? 1 : 0))
			ft_putbuffer(p, "0", 1);
	i = -1;
	if (pr > (p->nlen - 1) && fw < pr && nbr[0] == '-')
		while (i++ < pr - p->nlen)
			ft_putbuffer(p, "0", 1);
	else
		while ((pr > p->nlen) && ++i != pr - p->nlen + sign && pr < fw)
			ft_putbuffer(p, "0", 1);
	if (pr > 0 && fw >= 0 && ft_strcmp(nbr, "0") == 0 && p->zero == 0)
		ft_putbuffer(p, " ", 0);
	else if (fw > 0 && pr == 0 && ft_strcmp(nbr, "0") == 0 && p->zero == 0)
		ft_putbuffer(p, " ", 0);
	else if (fw >= 0 && pr >= 0 && ft_strcmp(nbr, "0") == 0 && p->zero == 0)
		ft_putbuffer(p, "", 0);
	else
		ft_putbuffer(p, nbr + sign, p->nlen);
	return (p);
}

t_print		*ft_intflag(t_print *p, char *nbr, int sign, int i)
{
	int		pr;
	int		fw;

	fw = p->fieldwidth;
	pr = p->precision;
	if (fw > pr && fw > 0 && pr > 0 && p->leftalign == 0 && sign != 1 && pr >= \
																p->nlen)
		while (++i < fw - pr + p->zero + ((p->sign == 0 && p->zero == 0) ? 1 : \
																			0))
			ft_putbuffer(p, " ", 1);
	else if (fw > pr && fw > 0 && pr > 0 && p->leftalign == 0 && sign == 1 && \
																pr >= p->nlen)
		while (++i < fw - pr + p->zero + ((p->sign == 0 && p->zero == 0) ? 1 : \
																	0) - sign)
			ft_putbuffer(p, " ", 1);
	if (sign)
		ft_putbuffer(p, "-", 1);
	else if (p->sign == 1)
		ft_putbuffer(p, ((nbr[0] == '-') ? "" : "+"), 1);
	else if (p->sign == 2)
		ft_putbuffer(p, ((nbr[0] == '-') ? "" : " "), 1);
	i = 1;
	return (ft_int_flag(p, nbr, sign, i));
}

t_print		*ft_intflags(t_print *p, char *nbr)
{
	int		i;
	int		sign;
	int		pr;
	int		fw;

	fw = p->fieldwidth;
	pr = p->precision;
	sign = ((nbr[0] == '-' && (p->zero == 1 || pr > p->nlen)) ? 1 : 0);
	i = 0;
	p->nlen = (int)ft_strlen(nbr);
	if (p->sign == 0 && p->leftalign != 1 && pr > fw)
		while (i++ < (pr - p->nlen) && sign == 0)
			ft_putbuffer(p, "0", 1);
	else if (p->leftalign != 1 && fw > pr && pr < p->nlen && !p->zero)
		while (i++ != fw - p->nlen && fw > p->nlen)
			ft_putbuffer(p, " ", 1);
	i = 0;
	p = ft_intflag(p, nbr, sign, i);
	i = -1;
	if (p->leftalign && fw > p->nlen)
		while (++i != fw - ((pr > p->nlen) ? pr : p->nlen) - p->sign % 2)
			ft_putbuffer(p, " ", 1);
	return (p);
}

t_print		*ft_decimal(t_print *p, va_list ap)
{
	char	*nbr;

	nbr = NULL;
	if (!(nbr = ft_strnew(0)))
		exit(-1);
	if (ft_strcmp(p->lmod, "ll") == 0)
		nbr = ft_itoa_base((intmax_t)((long long)va_arg(ap, intmax_t)), 10, 0);
	else if (ft_strcmp(p->lmod, "l") == 0)
		nbr = ft_itoa_base((intmax_t)((long)va_arg(ap, intmax_t)), 10, 0);
	else if (ft_strcmp(p->lmod, "h") == 0)
		nbr = ft_itoa_base((intmax_t)((short)va_arg(ap, intmax_t)), 10, 0);
	else if (ft_strcmp(p->lmod, "hh") == 0)
		nbr = ft_itoa_base((intmax_t)((signed char)va_arg(ap, intmax_t)), 10, \
																			0);
	else if (ft_strcmp(p->lmod, "j") == 0)
		nbr = ft_itoa_base((intmax_t)va_arg(ap, uintmax_t), 10, 0);
	else if (ft_strcmp(p->lmod, "z") == 0)
		nbr = ft_itoa_base((intmax_t)((signed long)va_arg(ap, intmax_t)), 10, \
																			0);
	else
		nbr = ft_itoa_base((intmax_t)((int)va_arg(ap, intmax_t)), 10, 0);
	p = ft_intflags(p, nbr);
	return (p);
}
