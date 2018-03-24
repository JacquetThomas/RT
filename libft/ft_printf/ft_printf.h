/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 19:40:53 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/02/17 17:00:24 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include "libft/libft.h"

# define BUFF_SIZE 126
# define FLAGS "sSpdDioOuUxXcC%"

typedef struct	s_print
{
	char		buff[BUFF_SIZE];
	char		*flags;
	char		lmod[3];
	char		conv;
	int			bufflen;
	int			hash;
	int			zero;
	int			leftalign;
	int			fieldwidth;
	int			sign;
	int			precision;
	int			ret;
	int			nlen;
	int			plen;
	int			len;
}				t_print;

t_print			*ft_useflag(t_print *p, char *n, char *pre, int len);
t_print			*ft_udecimal(t_print *p, va_list ap, char type);
t_print			*ft_getflag(char *str, t_print *p, va_list ap);
t_print			*ft_strings(t_print *p, va_list ap, char type);
t_print			*ft_putbuffer(t_print *p, char *src, int len);
t_print			*ft_octal(t_print *p, va_list ap, char type);
t_print			*ft_char(t_print *p, va_list ap, char type);
t_print			*ft_hexa(t_print *p, va_list ap, char type);
t_print			*ft_checkconvflag(t_print *p, va_list ap);
t_print			*ft_adress(t_print	*p, va_list ap);
t_print			*ft_decimal(t_print *p, va_list ap);
t_print			*ft_charpadding(t_print *p);
t_print			*ft_percent(t_print *p);
t_print			*ft_unknown(t_print *p);
t_print			*ft_reset(t_print *p);
t_print			ft_init(t_print *new);
t_print			*ft_zero(t_print *p);
void			ft_printbuffer(t_print *p, char c);
char			*ft_itoa_base_neg(uintmax_t n, int base, unsigned long len);
char			*ft_lenmod(t_print *p, int base, va_list ap, int l);
char			*ft_itoa_base(intmax_t n, int b, unsigned long l);
char			*ft_getnbr(char *str);
int				ft_countwords(const char *str, char c);
int				ft_printf(const char *format, ...);
int				ft_atoi_base(char *str, int base);
int				ft_pow(int nb, int power);
int				ft_validflags(t_print *p);
int				ft_putwchar(wchar_t c);
int				ft_wcharlen(wchar_t c);
int				ft_wstrlen(wchar_t *s);
int				ft_putwchar(wchar_t c);
int				ft_isflag(char c);
int				ft_nblen(int nb);

#endif
