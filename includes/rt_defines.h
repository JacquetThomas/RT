/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_defines.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 14:44:43 by bmoiroud          #+#    #+#             */
/*   Updated: 2018/03/17 16:26:28 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DEFINES_H
# define RT_DEFINES_H

# define WIN_H			800
# define WIN_W			1200
# define FOV			1.0472
# define HM_W			230
# define IM_W			300
# define SEP_H			24
# define CROSS_W		30
# define BOX_H			23
# define BOX_W			25
# define BUTTON_W		(IM_W - 60) / 3

# define EVENT_STOP		0
# define EVENT_IDLE		1
# define EVENT_UPDATE	2

# define ERR_SYS		0
# define ERR_CL			1
# define ERR_SDL		2
# define ERR_USAGE		3

# define COLOR			16711680
# define INTENSITY		100
# define ZOOM			1.1
# define PI				3.141596
# define MAX_RAND		5000
# define OBJS_MAX		50
# define LGTS_MAX		15
# define INT_MAX		2147483647
# define INT_MIN		-2147483648

# define ROT_SPEED		3.0
# define SPEED_V		1.5
# define SPEED_H		1.5

# define SPHERE			0
# define PLANE			1
# define CONE			2
# define CYLINDER		3
# define CUBE			4
# define FOCUS			5

# define CHESSBOARD 	1
# define BRICKS 		2
# define WOOD 			3
# define MARBLE 		4

# define CARTOON		1
# define SEPIA			2
# define BW				3

# define APERTURE		8
# define DOF_INT		200

#endif
