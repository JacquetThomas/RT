/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:50:02 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/02/18 14:50:51 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print		*ft_lmod(t_print *p)
{
	char	*s;
	int		l;

	l = ft_strlen(p->flags) - 1;
	s = p->flags;
	if ((s[l] == 'D' || s[l] == 'O' || s[l] == 'U') && s[l - 1] != 'l')
		ft_strcpy(p->lmod, "l");
	if ((s[l - 1] == 'l' || s[l - 1] == 'h' || s[l - 1] == 'j' || s[l - 1] == \
															'z') && s[l] != 'U')
		ft_strncat(p->lmod, &s[l - 1], 1);
	if ((s[l - 2] == 'l' || s[l - 2] == 'h') && l > 1 && s[l - 2] == s[l - 1])
		ft_strncat(p->lmod, &s[l - 1], 1);
	return (p);
}

t_print		*ft_precision(t_print *p)
{
	int		i;

	i = 0;
	while (p->flags[i] != '.' && p->flags[i])
		i++;
	if (p->flags[i])
	{
		p->precision = ft_atoi_base(ft_getnbr(p->flags + i + 1), 10);
		if (p->precision == -1)
			p->precision = 0;
	}
	return (p);
}

t_print		*ft_fieldwidth(t_print *p, va_list ap)
{
	int		i;

	i = 0;
	while (p->flags[i] == 32 || p->flags[i] == 35 || (p->flags[i] == 48 && \
			p->zero == 1) || p->flags[i] == 43 || p->flags[i] == 45)
		i++;
	if (p->flags[i] <= 57 && p->flags[i] >= 48)
		p->fieldwidth = ft_atoi_base(ft_getnbr(p->flags + i), 10);
	else if (p->flags[i] == '*')
		p->fieldwidth = va_arg(ap, int);
	return (p);
}

t_print		*ft_flags(t_print *p)
{
	int		i;

	i = 0;
	while (p->flags[i] == 32 || p->flags[i] == 35 || p->flags[i] == 43 || \
										p->flags[i] == 45 || p->flags[i] == 48)
	{
		if (p->flags[i] == ' ')
			p->sign = (p->sign == 1) ? (1) : (2);
		else if (p->flags[i] == '#')
			p->hash = 1;
		else if (p->flags[i] == '+')
			p->sign = 1;
		else if (p->flags[i] == '-')
			p->leftalign = 1;
		else if (p->flags[i] == '0')
			p->zero = 1;
		i++;
	}
	return (p);
}

t_print		*ft_getflag(char *str, t_print *p, va_list ap)
{
	int		i;

	i = 1;
	while (!ft_isflag(str[i]))
		i++;
	if (!(p->flags = ft_strnew(i + 1)))
		exit(-1);
	p->flags = ft_strncat(p->flags, str + 1, i);
	if ((int)ft_strlen(p->flags) > 0)
	{
		p = ft_flags(p);
		ft_validflags(p);
		p = ft_fieldwidth(p, ap);
		p = ft_precision(p);
		p = ft_lmod(p);
		p = ft_checkconvflag(p, ap);
	}
	return (p);
}
