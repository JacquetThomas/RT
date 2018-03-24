/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 14:07:52 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/13 15:49:13 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

double	ft_atod(char *str)
{
	double	ret;
	int		l;
	int		sign;

	sign = (str[0] == '-') ? -1 : 1;
	l = 0;
	while (str[l] && str[l] != '.')
		l++;
	if (l < (int)ft_strlen(str))
	{
		str[l] = '\0';
		l++;
		ret = ft_atoi(str) + sign * (ft_atoi(str + l) / \
									ft_fpow(10.0, (double)ft_strlen(str + l)));
	}
	else
		ret = ft_atoi(str);
	return (ret);
}
