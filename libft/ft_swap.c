/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 12:04:07 by bmoiroud          #+#    #+#             */
/*   Updated: 2016/11/22 17:06:26 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *a, void *b)
{
	*((unsigned char *)a) += *((unsigned char *)b);
	*((unsigned char *)b) = *((unsigned char *)a) - *((unsigned char *)b);
	*((unsigned char *)a) -= *((unsigned char *)b);
}
