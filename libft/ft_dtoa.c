/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 17:25:32 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/18 11:53:55 by cjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

static char	*is_neg(char *str, double d)
{
	char *tmp;

	if ((d > -1 && d < 0))
	{
		tmp = str;
		str = ft_strjoin("-", tmp);
		free(tmp);
	}
	return (str);
}

char		*ft_dtoa(double d, int p)
{
	double		d2;
	int			i;
	char		*str;
	char		*tmp[2];

	i = -1;
	str = ft_itoa((int)d);
	tmp[0] = str;
	str = ft_strjoin(tmp[0], ".");
	free(tmp[0]);
	d2 = fabs(d - (int)d);
	while (++i < p)
	{
		tmp[0] = str;
		d2 *= 10.0;
		tmp[1] = ft_itoa(d2);
		str = ft_strjoin(tmp[0], tmp[1]);
		free(tmp[0]);
		free(tmp[1]);
		d2 = d2 - (int)d2;
	}
	return (is_neg(str, d));
}
