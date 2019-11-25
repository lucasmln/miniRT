/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:34:05 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/25 15:34:55 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minirt.h"

void	ft_init(t_data *data)
{
	data->cam->next = NULL;
	data->cam->start = data->cam;
	data->light->next = NULL;
	data->light->start = data->light;
	data->sp->next = NULL;
	data->sp->start = data->sp;
	data->pl->next = NULL;
	data->pl->start = data->pl;
	data->sq->next = NULL;
	data->sq->start = data->sq;
	data->cy->next = NULL;
	data->cy->start = data->cy;
	data->tr->next = NULL;
	data->cy->start = data->cy;
}

int		ft_malloc_data(t_data	*data)
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
