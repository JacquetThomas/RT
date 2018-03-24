/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eferrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:01:02 by eferrand          #+#    #+#             */
/*   Updated: 2017/12/12 17:03:32 by eferrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h.cl"

//		printf("ray->coltype = %s\tray->colpos = %f %f %f\n", (rt->objects[hit].type == 0 ? "SPHERE" : (rt->objects[hit].type == 1 ? "PLANE" : (rt->objects[hit].type == 2 ? "CONE" : (rt->objects[hit].type == 3 ? "CYLINDER" : "CUBE")))), ray->colpos.x, ray->colpos.y, ray->colpos.z);



static void  check_col_neg(__global t_rt *rt, t_ray *ray, int hit)
{
	int         i = -1;
	int         last = hit;
	double		nearcol[1];
	t_vector	pos = ray->pos;
	double		dist[OBJS_MAX][2];

	while (rt->objects[hit].negative)
	{
		i = -1;
		last = hit;
        ray->t = 200000.0;
// enregistrement des distances de tous les objets sachant que pour un objet (collision 1 < collision 2) ||| dist[i][0] = collision 1 ||| dist[i][1] = collision 2
		while (++i < rt->nb_obj)
		{
        	ray->t = 200000.0;
        	ray->otherside = 200000.0;
			if (rt->objects[i].type == SPHERE)
				ft_sphere_col(rt->objects[i], ray);
			else if (rt->objects[i].type == PLANE)
				ft_plane_col(rt->objects[i], ray);
			else if (rt->objects[i].type == CONE)
				ft_cone_col(rt->objects[i], ray);
			else if (rt->objects[i].type == CYLINDER)
				ft_cyl_col(rt->objects[i], ray);
			else if (rt->objects[i].type == CUBE)
				ft_cube_col(rt->objects[i], ray);
            dist[i][0] = (ray->t != 200000.0) ? ray->t : -1;
            dist[i][1] = (ray->t != 200000.0) ? ray->otherside : -1;
        }

// ce while recherche la presence d autres objets negatifs imbriqués
		i = -1;
		while (i != rt->nb_obj)
		{
			while (++i < rt->nb_obj)
			{
				if (rt->objects[i].negative && dist[last][0] < dist[i][0] && dist[i][0] <= dist[last][1] && dist[last][1] < dist[i][1])
				{
					last = i;
					i = -1;
					break ;
				}
			}
		}

// ce while cherche l objet le plus proche apres le dernier negatif
		i = -1;
		*nearcol = 200000.0;
		while (++i < rt->nb_obj)
		{
			if (dist[last][1] < dist[i][0] && dist[i][0] < *nearcol)
			{
				hit = i;
				*nearcol = dist[i][0]; 
				i = -1;
			}
			else if (dist[last][1] < dist[i][1] && dist[i][1] < *nearcol)
			{
				hit = i;
				*nearcol = dist[i][1]; 
				i = -1;
			}
		}

// si rayon part dans le vide apres les negatifs
		if (*nearcol == 200000.0)
		{
			ray->t = 200000.0;
			ray->dist = 200000.0;
			ray->id = -1;
			return ;
		}

// recuperation des datas de collisions
		pos = ray->pos;
		ray->t = 200000.0;
		ray->pos += (*nearcol - 0.1) * ray->dir;
		if (rt->objects[hit].type == SPHERE)
			ft_sphere_col(rt->objects[hit], ray);
		else if (rt->objects[hit].type == PLANE)
			ft_plane_col(rt->objects[hit], ray);
		else if (rt->objects[hit].type == CONE)
			ft_cone_col(rt->objects[hit], ray);
		else if (rt->objects[hit].type == CYLINDER)
			ft_cyl_col(rt->objects[hit], ray);
		else if (rt->objects[hit].type == CUBE)
			ft_cube_col(rt->objects[hit], ray);
		ray->pos = pos;
		ray->id = hit;
		ray->dist = *nearcol;
		ray->t = *nearcol;
	}
}
