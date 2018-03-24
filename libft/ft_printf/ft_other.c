/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:12:03 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/02/16 20:20:35 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print		*ft_percent(t_print *p)
{
	int		i;

	i = -1;
	if (p->leftalign == 0)
		while (i++ < p->fieldwidth - 2)
		{
			if (p->zero == 1)
				p = ft_putbuffer(p, "0", 1);
			else
				p = ft_putbuffer(p, " ", 1);
		}
	p = ft_putbuffer(p, "%", 1);
	if (p->leftalign == 1)
		while (i++ < p->fieldwidth - 2)
		{
			if (p->zero == 1)
				p = ft_putbuffer(p, "0", 1);
			else
				p = ft_putbuffer(p, " ", 1);
		}
	return (p);
}

t_print		*ft_unknown(t_print *p)
{
	if (p->leftalign == 0)
		ft_charpadding(p);
	if (p->conv)
		ft_putbuffer(p, &p->conv, 0);
	if (p->leftalign == 1)
		ft_charpadding(p);
	return (p);
}

t_print		*ft_adress2(t_print *p, char *adress, int len)
{
	int i;

	i = 0;
	if (p->fieldwidth > len && p->leftalign == 0 && p->zero == 0)
		while (i++ < p->fieldwidth - len - 2)
			ft_putbuffer(p, " ", 1);
	ft_putbuffer(p, "0x", 2);
	if (p->fieldwidth > len && p->leftalign == 0 && p->zero == 1)
		while (i++ < p->fieldwidth - len - 2)
			ft_putbuffer(p, "0", 1);
	if (p->precision > len)
		while (++i < p->precision - len + ((p->fieldwidth != 0) ? 1 : 2))
			ft_putbuffer(p, "0", 1);
	if (!adress && p->precision >= 0)
		ft_putbuffer(p, "", 1);
	else if (!adress)
		ft_putbuffer(p, "0", 1);
	else
		ft_putbuffer(p, adress, 14);
	if (p->fieldwidth > len && p->leftalign == 1)
		while (i++ < p->fieldwidth - len - 2)
			ft_putbuffer(p, " ", 1);
	return (p);
}

t_print		*ft_adress(t_print *p, va_list ap)
{
	char	*adress;
	void	*adr;
	int		len;
	int		i;

	i = 0;
	len = 1;
	adr = va_arg(ap, void *);
	adress = NULL;
	if (adr != NULL)
		if ((adress = ft_itoa_base((intmax_t)adr, 16, sizeof(long))))
			while (adress[i])
			{
				adress[i] = ft_tolower(adress[i]);
				i++;
			}
	i = 0;
	if (adress)
		len = (int)ft_strlen(adress);
	p = ft_adress2(p, adress, len);
	free(adress);
	return (p);
}
