/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:25:06 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/02/27 17:55:34 by bmoiroud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

#define ft_interp(w, b, c) mix((b), (c), (w))

static double		ft_gradient(int a, t_vector v)
{
	const int3		grads[16] = { 
		{1, 1, 0}, {-1, 1, 0}, {1, -1, 0}, {-1, -1, 0}, \
		{1, 0, 1}, {-1, 0, 1}, {1, 0, -1}, {-1, 0, -1}, \
		{0, 1, 1}, {0, -1, 1}, {0, 1, -1}, {0, -1, -1}, \
		{1, 1, 0}, {-1, 1, 0}, {0, -1 ,1}, {0, -1, -1}
	};
	const int		i = a & 0x0f;
	const t_vector	v2 = {
		grads[i].x, \
		grads[i].y, \
		grads[i].z
	};
	
	return (dot(v, v2));
}

static double		ft_noise_weight(const double w)
{
	return (w * w * w * (w * (w * 6 - 15) + 10));
}

static double		ft_perlin_noise(const t_vector hit)
{
	const int	perm[256] = { 
		151, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 99, 37, \
		8, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 160, 137, \
		35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, \
		134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, \
		55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, \
		18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, \
		250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, \
		189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, \
		43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, \
		97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, \
		107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, \
		138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, \
		140, 36, 103, 30, 227, 47, 16, 58, 69, 17, 209, 76, 132, 187, 45, 127, \
		197, 62, 94, 252, 153, 101, 155, 167, 219, 182, 3, 64, 52, 217, 215, 61, \
		168, 68, 175, 74, 185, 112, 104, 218, 165, 246, 4, 150, 208, 254, 142, 71, \
		230, 220, 105, 92, 145, 235, 249, 14, 41, 239, 156, 180, 226, 89, 203, 117
	};
	
	const t_vector	v1 = {
		floor(hit.x), \
		floor(hit.y), \
		floor(hit.z)
	};
	const t_vector	v2 = {
		hit.x - v1.x, \
		hit.y - v1.y, \
		hit.z - v1.z
	};
	const t_vector	v3 = {
		v2.x - 1.0, \
		v2.y, \
		v2.z
	};
	const t_vector	v4 = {
		v2.x - 1.0, \
		v2.y - 1.0, \
		v2.z
	};
	const t_vector	v5 = {
		v2.x - 1.0, \
		v2.y, \
		v2.z - 1.0
	};
	const t_vector	v6 = {
		v2.x, \
		v2.y - 1.0, \
		v2.z
	};
	const t_vector	v7 = {
		v2.x, \
		v2.y - 1.0, \
		v2.z - 1.0
	};
	const t_vector	v8 = {
		v2.x, \
		v2.y, \
		v2.z - 1.0
	};
	const t_vector	v9 = {
		v2.x - 1.0, \
		v2.y - 1.0, \
		v2.z - 1.0
	};

	const int3		u1 = {
		(int)v1.x, \
		(int)v1.y, \
		(int)v1.z
	};
	const int3		u2 = {
		u1.x + 1, \
		u1.y + 1, \
		u1.z + 1
	};

	const int		p1 = perm[u1.x & 0x0ff];
	const int		p2 = perm[u2.x & 0x0ff];

	const int		p3 = perm[(p1 + u1.y) & 0x0ff];
	const int		p4 = perm[(p2 + u1.y) & 0x0ff];
	const int		p5 = perm[(p1 + u2.y) & 0x0ff];
	const int		p6 = perm[(p2 + u2.y) & 0x0ff];

	const int		p7 = perm[(p3 + u1.z) & 0x0ff];
	const int		p8 = perm[(p4 + u1.z) & 0x0ff];
	const int		p9 = perm[(p5 + u1.z) & 0x0ff];
	const int		p10 = perm[(p6 + u1.z) & 0x0ff];
	const int		p11 = perm[(p3 + u2.z) & 0x0ff];
	const int		p12 = perm[(p4 + u2.z) & 0x0ff];
	const int		p13 = perm[(p5 + u2.z) & 0x0ff];
	const int		p14 = perm[(p6 + u2.z) & 0x0ff];

	const double	g1 = ft_gradient(p7, v2);
	const double	g2 = ft_gradient(p8, v3);
	const double	g3 = ft_gradient(p9, v6);
	const double	g4 = ft_gradient(p10, v4);
	const double	g5 = ft_gradient(p11, v8);
	const double	g6 = ft_gradient(p12, v5);
	const double	g7 = ft_gradient(p13, v7);
	const double	g8 = ft_gradient(p14, v9);

	const t_vector	w = {
		ft_noise_weight(v2.x), \
		ft_noise_weight(v2.y), \
		ft_noise_weight(v2.z)
	};
	
	return (\
		ft_interp(w.z, \
			ft_interp(w.y, \
				ft_interp(w.x, g1, g2), \
				ft_interp(w.x, g3, g4)), \
			ft_interp(w.y, \
				ft_interp(w.x, g5, g6), \
				ft_interp(w.x, g7, g8) \
				) \
			) \
		);
}