/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 19:40:46 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/02/17 18:07:03 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printbuffer(t_print *p, char c)
{
	int		l;

	l = (int)ft_strlen(p->buff);
	ft_putstr(p->buff);
	p->bufflen += l;
	ft_bzero(p->buff, l);
	p->ret += l;
	if (c == 0)
		write(1, &c, 1);
}

t_print		*ft_putbuffer(t_print *p, char *src, int len)
{
	int		i;
	int		j;

	j = 0;
	i = -1;
	((src == 0) ? ft_printbuffer(p, 0) : src);
	if (src != 0)
	{
		p->bufflen = (int)ft_strlen(p->buff);
		while (i++ < len)
		{
			p->buff[i + p->bufflen] = src[j];
			if (((i + p->bufflen) % BUFF_SIZE == 0) && i != 0)
			{
				write(1, p->buff, BUFF_SIZE);
				ft_bzero(p->buff, BUFF_SIZE);
				p->ret += BUFF_SIZE;
				p->bufflen += i;
				len -= i;
				i = -1;
			}
			j++;
		}
	}
	return (p);
}

t_print		ft_parse(char *str, t_print *p, va_list ap)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tmp = str;
	while (str[i])
	{
		if (str[i] == '%')
		{
			p = ft_putbuffer(p, tmp + j, i - j - 1);
			p = ft_getflag(str + i, p, ap);
			i += ft_strlen(p->flags) + 1;
			j = i;
		}
		else if (i == BUFF_SIZE)
			p = ft_putbuffer(p, tmp + j, i);
		else
			i++;
		p = ft_reset(p);
	}
	if (j != i)
		p = ft_putbuffer(p, tmp + j, i - j);
	return (*p);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	t_print		p;
	int			ret;

	ret = 0;
	va_start(ap, format);
	p = ft_init(&p);
	p = ft_parse((char *)format, &p, ap);
	va_end(ap);
	ft_putstr(p.buff);
	p.ret += ft_strlen(p.buff);
	return (p.ret);
}
