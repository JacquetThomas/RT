/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:45:41 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/02/16 18:25:03 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_checkflag(char *flags, char *conv, int l)
{
	if (conv[l] != 'o' && conv[l] != 'u')
		return (0);
	if ((ft_strcmp(flags, "l") == 0 || ft_strcmp(flags, "ll") == 0))
		return (1);
	if ((ft_strcmp(flags, "z") == 0 || ft_strcmp(flags, "j") == 0))
		return (1);
	if (ft_strcmp(flags, "h") == 0 || ft_strcmp(flags, "hh") == 0)
		return (0);
	return (0);
}

char		*ft_lenmod(t_print *p, int b, va_list ap, int l)
{
	char		*nb;

	nb = NULL;
	if (ft_checkflag(p->lmod, p->flags, l) == 1)
		nb = ft_itoa_base_neg((uintmax_t)va_arg(ap, unsigned long), b, 15);
	else if (ft_strcmp(p->lmod, "ll") == 0)
		nb = ft_itoa_base((intmax_t)va_arg(ap, uintmax_t), b, 12);
	else if (ft_strcmp(p->lmod, "l") == 0)
		nb = ft_itoa_base((intmax_t)(unsigned long)va_arg(ap, intmax_t), b, 8);
	else if (ft_strcmp(p->lmod, "h") == 0)
		nb = ft_itoa_base((intmax_t)(unsigned short)va_arg(ap, intmax_t), b, 2);
	else if (ft_strcmp(p->lmod, "hh") == 0)
		nb = ft_itoa_base((intmax_t)(unsigned char)va_arg(ap, intmax_t), b, 1);
	else if (ft_strcmp(p->lmod, "j") == 0)
		nb = ft_itoa_base(va_arg(ap, intmax_t), b, sizeof(intmax_t));
	else if (ft_strcmp(p->lmod, "z") == 0)
		nb = ft_itoa_base((intmax_t)(size_t)va_arg(ap, intmax_t), b, 8);
	else if (p->flags[l] == 'u' || p->flags[l] == 'o')
		nb = ft_itoa_base((intmax_t)(unsigned int)va_arg(ap, intmax_t), b, 4);
	else
		nb = ft_itoa_base((intmax_t)(int)va_arg(ap, intmax_t), b, sizeof(int));
	return (nb);
}

t_print		*ft_checkconvflag(t_print *p, va_list ap)
{
	int		l;

	l = ft_strlen(p->flags) - 1;
	if (p->flags[l] == 'd' || p->flags[l] == 'i' || p->flags[l] == 'D')
		p = ft_decimal(p, ap);
	else if (p->flags[l] == 'x' || p->flags[l] == 'X')
		p = ft_hexa(p, ap, p->flags[l]);
	else if (p->flags[l] == 'o' || p->flags[l] == 'O')
		p = ft_octal(p, ap, p->flags[l]);
	else if (p->flags[l] == 'u' || p->flags[l] == 'U')
		p = ft_udecimal(p, ap, p->flags[l]);
	else if (p->flags[l] == 'c' || p->flags[l] == 'C')
		p = ft_char(p, ap, p->flags[l]);
	else if (p->flags[l] == 's' || p->flags[l] == 'S')
		p = ft_strings(p, ap, p->flags[l]);
	else if (p->flags[l] == 'p')
		p = ft_adress(p, ap);
	else if (p->flags[l] == '%')
		p = ft_percent(p);
	else
		p = ft_unknown(p);
	return (p);
}
