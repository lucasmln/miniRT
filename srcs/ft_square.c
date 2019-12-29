/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_square.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:56:46 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/19 13:54:02 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

double		ft_for_each_square(t_ray ray, t_vect3 *p, t_vect3 *n)
{
	double		inter;
	int			pos[2];
	double		min;

	min = -1;
	while (1)
	{
		while (1)
		{
			inter = ft_intersection_ray_tr(ray, g_data->sq->tr, p, n);
			if (inter != 0)
				if (min == -1 || fmin(inter, min) == inter)
				{
					min = inter;
					pos[0] = g_data->sq->rank;
					pos[1] = g_data->sq->tr->rank;
				}
			if (g_data->sq->tr->rank == -1)
				break ;
			g_data->sq->tr = g_data->sq->tr->next;
		}
		g_data->sq->tr = g_data->sq->tr->next;
		if (g_data->sq->rank == -1)
			break ;
		g_data->sq = g_data->sq->next;
	}
	if (min > 0)
		while (g_data->sq->rank != pos[0])
			g_data->sq = g_data->sq->next;
	if (min > 0)
		while (g_data->sq->tr->rank != pos[1])
			g_data->sq->tr = g_data->sq->tr->next;
	return (ft_intersection_ray_tr(ray, g_data->sq->tr, p, n));
}

void		ft_create_square_point(t_square *sq)
{
	sq->tr->p_1.x = sq->coord.x - ((sq->height / 2)) * sq->dir.x;
	sq->tr->p_1.y = sq->coord.y - ((sq->height / 2)) * sq->dir.y;
	sq->tr->p_1.z = sq->coord.z - ((sq->height / 2)) * sq->dir.z;
	sq->tr->p_2.x = sq->coord.x - ((sq->height / 2)) * sq->dir.x;
	sq->tr->p_2.y = sq->coord.y + ((sq->height / 2)) * sq->dir.y;
	sq->tr->p_2.z = sq->coord.z + ((sq->height / 2)) * sq->dir.z;
	sq->tr->p_3.x = sq->coord.x + ((sq->height / 2)) * sq->dir.x;
	sq->tr->p_3.y = sq->coord.y + ((sq->height / 2)) * sq->dir.y;
	sq->tr->p_3.z = sq->coord.z + ((sq->height / 2)) * sq->dir.z;
	sq->tr = sq->tr->next;
	sq->tr->p_3.x = sq->coord.x + ((sq->height / 2)) * sq->dir.x;
	sq->tr->p_3.y = sq->coord.y - ((sq->height / 2)) * sq->dir.y;
	sq->tr->p_3.z = sq->coord.z - ((sq->height / 2)) * sq->dir.z;
	sq->tr->p_1 = sq->tr->next->p_1;
	sq->tr->p_2 = sq->tr->next->p_3;
	sq->tr = sq->tr->next;
	sq->tr = sq->tr->next;
	sq->tr = sq->tr->next;
}
