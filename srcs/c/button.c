/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjacquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 14:54:15 by cjacquet          #+#    #+#             */
/*   Updated: 2018/03/09 17:59:53 by cjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	on_button(int x, int y)
{
	return (x >= WIN_W - IM_W + 20 && x <= WIN_W - 20 && \
			y >= 10 * SEP_H + SEP_H && y <= 11 * SEP_H + SEP_H);
}

int	on_exit_cross(int x, int y)
{
	return (x >= 0 && x <= CROSS_W && y >= 0 && y <= SEP_H);
}

int	on_reduce(int x, int y)
{
	return (x >= CROSS_W && x <= CROSS_W * 2 && y >= 0 && y <= SEP_H);
}

int	on_screenshot(int x, int y)
{
	return (x >= WIN_W - IM_W + 20 && x <= WIN_W - 20 && \
			y >= 12 * SEP_H + SEP_H && y <= 13 * SEP_H + SEP_H);
}

int	on_title_bar(int x, int y)
{
	return (x >= 0 && x <= WIN_W && y >= 0 && y <= SEP_H);
}
