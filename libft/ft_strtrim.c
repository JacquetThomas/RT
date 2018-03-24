/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:49:44 by bmoiroud          #+#    #+#             */
/*   Updated: 2017/12/04 15:45:28 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *str)
{
	char *se;

	if (str == NULL)
		return (NULL);
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	if (*str == '\0')
		return (ft_strnew(0));
	se = (char *)str + ft_strlen(str) - 1;
	while (*se == ' ' || *se == '\t' || *se == '\n')
		se--;
	return (ft_strsub(str, 0, (se - str + 1)));
}
