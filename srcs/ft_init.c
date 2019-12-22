/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:34:05 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/22 19:26:34 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	ft_init(t_data *data)
{
	data->cam->next = NULL;
	data->cam->rank = 0;
	data->light->next = NULL;
	data->light->rank = 0;
	data->sp->next = NULL;
	data->sp->rank = 0;
	data->pl->next = NULL;
	data->pl->rank = 0;
	data->sq->next = NULL;
	data->sq->rank = 0;
	data->cy->next = NULL;
	data->cy->rank = 0;
	data->tr->next = NULL;
	data->cy->rank = 0;
	data->obj = "";
	data->check_trans = 0;
	data->check_mir = 0;
}

int		ft_malloc_data(t_data *data)
{
	if (!(data->cam = malloc(sizeof(t_cam) * 1)))
		return (-1);
	if (!(data->light = malloc(sizeof(t_light) * 1)))
		return (-1);
	if (!(data->sp = malloc(sizeof(t_sphere) * 1)))
		return (-1);
	if (!(data->pl = malloc(sizeof(t_plane) * 1)))
		return (-1);
	if (!(data->sq = malloc(sizeof(t_square) * 1)))
		return (-1);
	if (!(data->cy = malloc(sizeof(t_cylinder) * 1)))
		return (-1);
	if (!(data->tr = malloc(sizeof(t_triangle) * 1)))
		return (-1);
	return (0);
}

int		ft_init_tr_in_sq(t_square *sq)
{
	if (!(sq->tr = malloc(sizeof(t_triangle))))
		return (-1);
	if (!(sq->tr->next = malloc(sizeof(t_triangle))))
		return (-1);
	sq->tr->rank = 1;
	sq->tr->next->next = sq->tr;
	sq->tr->next->rank = -1;
	sq->tr->color = sq->color;
	sq->tr->next->color = sq->color;
	return (1);
}

void	ft_set_obj_coord(t_data *data)
{
	t_vect3		abs_cam;
	int			cmp;

	ft_go_start_lst(data, "all obj");
	abs_cam = data->cam->coord;
		while (1)
		{
			data->sp->coord = ft_vec_diff(data->sp->coord, abs_cam);
			data->sp->coord = ft_vect_multiplication(data->sp->coord, data->cam->dir);
			if (data->sp->rank == -1)
				break;
			data->sp = data->sp->next;
		}
		while (1)
		{
			data->pl->coord = ft_vec_diff(data->pl->coord, abs_cam);
			data->pl->coord = ft_vect_multiplication(data->pl->coord, data->cam->dir);
			if (data->pl->rank == -1)
				break;
			data->pl = data->pl->next;
		}
		while (1)
		{
			data->sq->coord = ft_vec_diff(data->sq->coord, abs_cam);
			data->sq->coord = ft_vect_multiplication(data->sq->coord, data->cam->dir);
			while (data->sq->tr->rank != -1)
				data->sq->tr = data->sq->tr->next;
			data->sq->tr = data->sq->tr->next;
			cmp = 0;
			while (cmp != 2)
			{
				data->sq->tr->p_1 = ft_vec_diff(data->sq->tr->p_1, abs_cam);
				data->sq->tr->p_1 = ft_vect_multiplication(data->sq->tr->p_1, data->cam->dir);
				data->sq->tr->p_2 = ft_vec_diff(data->sq->tr->p_2, abs_cam);
				data->sq->tr->p_2 = ft_vect_multiplication(data->sq->tr->p_2, data->cam->dir);
				data->sq->tr->p_3 = ft_vec_diff(data->sq->tr->p_3, abs_cam);
				data->sq->tr->p_3 = ft_vect_multiplication(data->sq->tr->p_3, data->cam->dir);
				data->sq->tr = data->sq->tr->next;
				cmp++;
			}
			if (data->sq->rank == -1)
				break;
			data->sq = data->sq->next;
		}
		while (1)
		{
			data->tr->p_1 = ft_vec_diff(data->tr->p_1, abs_cam);
			data->tr->p_1 = ft_vect_multiplication(data->tr->p_1, data->cam->dir);
			data->tr->p_2 = ft_vec_diff(data->tr->p_2, abs_cam);
			data->tr->p_2 = ft_vect_multiplication(data->tr->p_2, data->cam->dir);
			data->tr->p_3 = ft_vec_diff(data->tr->p_3, abs_cam);
			data->tr->p_3 = ft_vect_multiplication(data->tr->p_3, data->cam->dir);
			if (data->tr->rank == -1)
				break;
			data->tr = data->tr->next;
		}
		while (1)
		{
			data->cy->coord = ft_vec_diff(data->cy->coord, abs_cam);
			data->cy->coord = ft_vect_multiplication(data->cy->coord, data->cam->dir);
			if (data->cy->rank == -1)
				break;
			data->cy = data->cy->next;
		}
		while (1)
		{
			data->light->coord = ft_vec_diff(data->light->coord, abs_cam);
			data->light->coord = ft_vect_multiplication(data->light->coord, data->cam->dir);
			if (data->cy->rank == -1)
				break;
			data->light = data->light->next;
		}
		data->cam->coord.x = 1;
		data->cam->coord.y = 1;
		data->cam->coord.z = 1;
}
