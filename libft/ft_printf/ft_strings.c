/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 18:12:00 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/02/17 17:46:07 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_wstrpadding(t_print *p, wchar_t *s)
{
	int		len;
	int		i;
	int		j;

	j = 0;
	i = 0;
	len = 0;
	if (p->precision != -1)
		while (s[i] && len + (j = ft_wcharlen(s[i])) <= p->precision)
		{
			len = ((len == 0 && j > 1) ? -1 : len);
			len += j;
			i++;
		}
	else
		len = ft_wstrlen(s);
	i = 0;
	if (p->fieldwidth > p->precision && p->precision > 1)
		i = 1;
	if (p->fieldwidth > len)
		while (i++ < p->fieldwidth - len)
			ft_putbuffer(p, ((p->zero == 1) ? "0" : " "), 1);
}

t_print		*ft_wstr(t_print *p, int i, int j, wchar_t *s)
{
	if (p->leftalign == 0)
		ft_wstrpadding(p, s);
	ft_printbuffer(p, -1);
	while (s[i] && j != p->precision)
	{
		j += ft_wcharlen(s[i]);
		if (j <= p->precision && p->precision != -1)
			p->ret += ft_putwchar(s[i]);
		else if (p->precision == -1)
			p->ret += ft_putwchar(s[i]);
		else
			return (p);
		i++;
	}
	if (p->leftalign == 1)
		ft_wstrpadding(p, s);
	return (p);
}

t_print		*ft_unistr(t_print *p, va_list ap)
{
	int		i;
	int		j;
	wchar_t	*s;

	j = 0;
	i = 0;
	s = va_arg(ap, wchar_t *);
	if (s == NULL)
		ft_putbuffer(p, ("(null)"), 6);
	else
		p = ft_wstr(p, i, j, s);
	return (p);
}

t_print		*ft_strpadding(t_print *p, int len)
{
	int		i;
	int		pr;
	int		fw;

	fw = p->fieldwidth;
	pr = p->precision;
	i = 0;
	if (fw > pr && pr > 0 && pr < len)
		len = pr;
	else if (fw > pr)
		len = pr - (pr - len);
	else if (pr > fw && pr > len)
		len = fw - len;
	else if (fw > len)
		len = fw - len + 1;
	if (pr == 0 && fw > 0)
		len = 0;
	while (i++ < fw - len && len >= 0)
		ft_putbuffer(p, ((p->zero == 1) ? "0" : " "), 1);
	return (p);
}

t_print		*ft_strings(t_print *p, va_list ap, char type)
{
	char	*s;
	int		i;
	int		l;

	l = 0;
	i = 0;
	if (type == 'S' || ft_strcmp(p->lmod, "l") == 0)
		ft_unistr(p, ap);
	else
	{
		s = va_arg(ap, char *);
		if (s)
			l = (int)ft_strlen(s);
		if (p->leftalign == 0 && p->fieldwidth != 0)
			ft_strpadding(p, l);
		if (s == NULL && p->fieldwidth == 0)
			ft_putbuffer(p, "(null)", 6);
		else if (s && p->precision == -1 && p->fieldwidth == 0)
			ft_putbuffer(p, s, l);
		else if (s)
			ft_putbuffer(p, s, ((p->precision > -1) ? p->precision - 1 : l));
		if (p->leftalign == 1 && p->fieldwidth != -1)
			ft_strpadding(p, l);
	}
	return (p);
}
