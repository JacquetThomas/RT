/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrflags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:53:59 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/02/17 17:20:51 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print		*ft_use_flags(t_print *p, char *n, char *pre, int i)
{
	int		pr;
	int		fw;

	fw = p->fieldwidth;
	pr = p->precision;
	if (fw > pr && pr > 0 && !pre)
		while (i++ < fw - pr)
			ft_putbuffer(p, " ", 1);
	i = -1;
	if (p->hash && ft_strcmp(n, "0") != 0 && pre && fw > pr && p->zero == 0)
		ft_putbuffer(p, pre, p->plen);
	if (fw >= 0 && pr >= 0 && n[0] == '0')
		ft_putbuffer(p, "", p->nlen);
	else
		ft_putbuffer(p, n, p->nlen);
	if (p->leftalign == 1 && fw > pr)
		while (i++ < fw - p->nlen - 1 - ((pr > p->nlen) ? pr - p->nlen : 0))
			ft_putbuffer(p, " ", 1);
	return (p);
}

t_print		*ft_useflags(t_print *p, char *n, char *pre, int i)
{
	int		pr;
	int		fw;

	fw = p->fieldwidth;
	pr = p->precision;
	if (pr > p->nlen)
	{
		i = -1;
		while (++i < pr - p->nlen + ((p->plen == 2) ? 2 : 0))
			ft_putbuffer(p, "0", 1);
	}
	else if ((p->leftalign == 0 || pr > 0) && p->len > 0)
		while (++i < p->len + 1)
		{
			if (p->zero == 1 || (pr > 0 && i < pr - p->nlen))
				ft_putbuffer(p, "0", 1);
			else
				ft_putbuffer(p, " ", 1);
		}
	return (ft_use_flags(p, n, pre, 0));
}

t_print		*ft_useflag(t_print *p, char *n, char *pre, int len)
{
	int		i;
	int		pr;
	int		fw;

	fw = p->fieldwidth;
	pr = p->precision;
	p->plen = (int)ft_strlen(pre);
	p->nlen = (int)ft_strlen(n) + p->plen;
	p->len = len;
	i = -1;
	if (fw > pr && p->leftalign == 0 && p->nlen < pr)
		while (++i < (fw - ((pr > p->nlen) ? pr : p->nlen)))
			ft_putbuffer(p, " ", 1);
	else if (fw > pr && pr > 0 && pre && p->leftalign == 0)
		while (i++ < fw - ((p->nlen > pr) ? p->nlen + 1 : pr))
			ft_putbuffer(p, " ", 1);
	else if (p->hash == 1 && fw > p->nlen && p->leftalign == 0 && p->zero == 0 \
									&& p->flags[ft_strlen(p->flags) - 1] == 'o')
		while (i++ < fw - p->nlen - 1)
			ft_putbuffer(p, " ", 1);
	if (p->hash && ft_strcmp(n, "0") != 0 && pre && (fw <= pr || p->zero == 1))
		ft_putbuffer(p, pre, p->plen);
	return (ft_useflags(p, n, pre, i));
}
