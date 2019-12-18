/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:34:05 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/18 15:20:49 by lmoulin          ###   ########.fr       */
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
