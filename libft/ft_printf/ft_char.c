/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 15:19:55 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/02/14 18:46:35 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print		*ft_unichar(t_print *p, va_list ap)
{
	wchar_t	c;

	c = va_arg(ap, wchar_t);
	ft_printbuffer(p, -1);
	p->ret += ft_putwchar(c);
	return (p);
}

t_print		*ft_charpadding(t_print *p)
{
	int		i;

	i = 0;
	while (i < p->fieldwidth - 1)
	{
		if (p->zero == 1)
			ft_putbuffer(p, "0", 1);
		else
			ft_putbuffer(p, " ", 1);
		i++;
	}
	return (p);
}

t_print		*ft_char(t_print *p, va_list ap, char type)
{
	char	c;

	c = 0;
	if (type == 'C' || ft_strcmp(p->lmod, "l") == 0)
		p = ft_unichar(p, ap);
	else
	{
		c = (char)va_arg(ap, int);
		if (p->fieldwidth != 0 && p->leftalign == 0)
			p = ft_charpadding(p);
		if (c == 0)
			ft_putbuffer(p, 0, 0);
		else
			ft_putbuffer(p, &c, 0);
		if (p->fieldwidth != 0 && p->leftalign == 1)
			p = ft_charpadding(p);
		if (c == '\0')
			p->ret++;
	}
	return (p);
}
