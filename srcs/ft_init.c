/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:34:05 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/18 20:50:13 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	ft_init(void)
{
	g_data->cam->next = NULL;
	g_data->cam->rank = 0;
	g_data->light->next = NULL;
	g_data->light->rank = 0;
	g_data->sp->next = NULL;
	g_data->sp->rank = 0;
	g_data->pl->next = NULL;
	g_data->pl->rank = 0;
	g_data->sq->next = NULL;
	g_data->sq->rank = 0;
	g_data->cy->next = NULL;
	g_data->cy->rank = 0;
	g_data->tr->next = NULL;
	g_data->tr->rank = 0;
	g_data->obj = "";
	g_data->check_trans = 0;
	g_data->check_mir = 0;
	g_data->image->rank = 0;
	g_data->image->next = NULL;
}

int		ft_malloc_data(void)
{
	if (!(g_data = malloc(sizeof(struct s_data) * 1)))
		ft_print_error(-1);
	if (!(g_mlx.ptr = malloc(sizeof(void*) * 1)))
		ft_print_error(-1);
	if (!(g_mlx.win = malloc(sizeof(void*) * 1)))
		ft_print_error(-1);
	if (!(g_data->cam = malloc(sizeof(t_cam) * 1)))
		ft_print_error(-1);
	if (!(g_data->light = malloc(sizeof(t_light) * 1)))
		ft_print_error(-1);
	if (!(g_data->sp = malloc(sizeof(t_sphere) * 1)))
		ft_print_error(-1);
	if (!(g_data->pl = malloc(sizeof(t_plane) * 1)))
		ft_print_error(-1);
	if (!(g_data->sq = malloc(sizeof(t_square) * 1)))
		ft_print_error(-1);
	if (!(g_data->cy = malloc(sizeof(t_cylinder) * 1)))
		ft_print_error(-1);
	if (!(g_data->tr = malloc(sizeof(t_triangle) * 1)))
		ft_print_error(-1);
	if (!(g_data->image = malloc(sizeof(t_image) * 1)))
		ft_print_error(-1);
	ft_init();
	return (0);
}

int		ft_init_tr_in_sq(t_square *sq)
{
	if (!(sq->tr = malloc(sizeof(t_triangle))))
		ft_print_error(-1);
	if (!(sq->tr->next = malloc(sizeof(t_triangle))))
		ft_print_error(-1);
	sq->tr->rank = 1;
	sq->tr->next->next = sq->tr;
	sq->tr->next->rank = -1;
	sq->tr->color = sq->color;
	sq->tr->next->color = sq->color;
	return (1);
}
