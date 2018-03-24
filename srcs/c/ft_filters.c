/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:53:42 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/17 16:46:31 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			gx(uint32_t *img, int k, int j, int c)
{
	int			i;
	int			sum;
	const int	tab[3][3] = {
		{-1, 0, 1}, \
		{-2, 0, 2}, \
		{-1, 0, 1}
	};
	int			res;

	res = 0;
	while (++j < 2)
	{
		i = -2;
		while (++i < 2)
		{
			c = img[(j * WIN_W + i) + k];
			sum = ((c & 0xff) + (c >> 8 & 0xff) + (c >> 16 & 0xff)) / 3;
			res += tab[j + 1][i + 1] * sum;
		}
	}
	return (res);
}

int			gy(uint32_t *img, int k, int j, int c)
{
	int			i;
	int			sum;
	const int	tab[3][3] = {
		{-1, -2, -1}, \
		{0, 0, 0}, \
		{1, 2, 1}
	};
	int			res;

	res = 0;
	while (++j < 2)
	{
		i = -2;
		while (++i < 2)
		{
			c = img[(j * WIN_W + i) + k];
			sum = ((c >> 16 & 0xff) + (c >> 8 & 0xff) + (c & 0xff)) / 3;
			res += tab[j + 1][i + 1] * sum;
		}
	}
	return (res);
}

int			ft_limit_color(int color)
{
	if (color == 0)
		return (0);
	else if (color <= 50 && color > 0)
		return (25);
	else if (color <= 100 && color > 50)
		return (75);
	else if (color <= 150 && color > 100)
		return (125);
	else if (color <= 200 && color > 150)
		return (175);
	else if (color <= 250 && color > 200)
		return (225);
	return (255);
}

void		ft_cartoon(uint32_t *img)
{
	t_color	c;
	int		i;
	int		x;
	int		y;
	int		g;

	g = 0;
	y = 0;
	x = 0;
	i = -1;
	while (++i < (WIN_H * WIN_W))
	{
		c.c = img[i];
		c.b = c.c & 0xff;
		c.g = c.c >> 8 & 0xff;
		c.r = c.c >> 16 & 0xff;
		x = gx(img, i, -2, 0);
		y = gy(img, i, -2, 0);
		g = sqrt((x * x) + (y * y));
		img[i] = 0xff << 24 | ft_limit_color(c.r) << 16 | \
			ft_limit_color(c.g) << 8 | ft_limit_color(c.b);
	}
}

void		ft_sepia(uint32_t *img)
{
	t_color	c;
	t_color	c2;
	int		i;

	i = -1;
	while (++i < (WIN_H * WIN_W))
	{
		c.c = img[i];
		c.b = c.c & 0xff;
		c.g = (c.c >> 8) & 0xff;
		c.r = (c.c >> 16) & 0xff;
		c2.r = (c.r * 0.393) + (c.g * 0.769) + (c.b * 0.189);
		c2.r = (c2.r > 255) ? 255 : c2.r;
		c2.g = (c.r * 0.349) + (c.g * 0.686) + (c.b * 0.168);
		c2.g = (c2.g > 255) ? 255 : c2.g;
		c2.b = (c.r * 0.272) + (c.g * 0.534) + (c.b * 0.131);
		c2.b = (c2.b > 255) ? 255 : c2.b;
		img[i] = (0xff << 24) | (c2.r << 16) | (c2.g << 8) | c2.b;
	}
}
