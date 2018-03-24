/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 14:51:04 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/02/18 14:50:51 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print		*ft_hex(t_print *p, char *nbr, char *prefix, int nblen)
{
	if (nbr[0] == '0' && p->precision != -1)
	{
		nbr[0] = '\0';
		if (p->fieldwidth > 0)
			nblen++;
	}
	return (p = ft_useflag(p, nbr, prefix, nblen));
}

t_print		*ft_hexa(t_print *p, va_list ap, char type)
{
	char	*nbr;
	char	prefix[3];
	int		i;
	int		nblen;

	nblen = 0;
	i = -1;
	ft_bzero(prefix, 3);
	if (!(nbr = ft_strjoin(ft_strnew(0), ft_lenmod(p, 16, ap, 0))))
		exit(-1);
	if (p->hash == 1 && nbr[0] != '0')
		ft_strncat(prefix, ((type == 'X') ? "0X" : "0x"), 2);
	nblen = (int)ft_strlen(nbr) + (int)ft_strlen(prefix);
	if (type == 'x')
		while (nbr[++i])
			nbr[i] = ft_tolower(nbr[i]);
	nblen = (p->precision != -1 && p->fieldwidth == 0) ? p->precision - nblen -\
												1 : p->fieldwidth - nblen - 1;
	p = ft_hex(p, nbr, prefix, nblen);
	free(nbr);
	return (p);
}

t_print		*ft_octal(t_print *p, va_list ap, char type)
{
	char	*nbr;
	char	prefix[3];
	int		nblen;

	nblen = 0;
	ft_bzero(prefix, 3);
	if (!(nbr = ft_strnew(0)))
		exit(-1);
	if (type == 'O')
		ft_strncat(p->lmod, "l", 1);
	if (p->hash == 1)
		ft_strncat(prefix, "0", 1);
	if (!(nbr = ft_strjoin(nbr, ft_lenmod(p, 8, ap, ft_strlen(p->flags) - 1))))
		exit(-1);
	if (nbr[0] == '0' && p->precision != -1)
		ft_bzero(nbr, 1);
	nblen = (int)ft_strlen(nbr) + (int)ft_strlen(prefix);
	if (p->precision > nblen)
		nblen = p->precision - nblen - 1;
	else
		nblen = p->fieldwidth - nblen - 1;
	p = ft_useflag(p, nbr, prefix, nblen);
	free(nbr);
	return (p);
}

t_print		*ft_udecimal(t_print *p, va_list ap, char type)
{
	char	*nbr;
	char	*tmp;
	int		nblen;
	int		flen;

	flen = (int)ft_strlen(p->flags) - 1;
	nblen = 0;
	if (!(nbr = ft_strnew(0)))
		exit(-1);
	tmp = NULL;
	if (type == 'U')
		p->flags[flen] = 'u';
	tmp = nbr;
	if (!(nbr = ft_strjoin(nbr, ft_lenmod(p, 10, ap, flen))))
		exit(-1);
	free(tmp);
	nblen = (int)ft_strlen(nbr);
	if (p->precision > nblen)
		nblen = p->precision - nblen - 1;
	else
		nblen = p->fieldwidth - nblen - 1;
	p = ft_useflag(p, nbr, "", nblen);
	free(nbr);
	return (p);
}
