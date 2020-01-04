/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:34:05 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/04 02:16:00 by lmoulin          ###   ########.fr       */
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
}

int		ft_malloc_data(void)
{
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

void	ft_set_obj_coord(void)
{
	t_vect3		abs_cam;
	int			cmp;

	ft_go_start_lst("all obj");
	abs_cam = g_data->cam->coord;
	while (g_data->sp->rank != 0)
	{
		g_data->sp->coord = ft_vec_diff(g_data->sp->coord, abs_cam);
		g_data->sp->coord = ft_vect_multiplication(g_data->sp->coord, g_data->cam->dir);
		if (g_data->sp->rank == -1)
			break ;
		g_data->sp = g_data->sp->next;
	}
	while (g_data->pl->rank != 0)
	{
		g_data->pl->coord = ft_vec_diff(g_data->pl->coord, abs_cam);
		g_data->pl->coord = ft_vect_multiplication(g_data->pl->coord, g_data->cam->dir);
		if (g_data->pl->rank == -1)
			break ;
		g_data->pl = g_data->pl->next;
	}
	if (g_data->sq->next != NULL)
		while (g_data->sq->rank != 0)
		{
			g_data->sq->coord = ft_vec_diff(g_data->sq->coord, abs_cam);
			g_data->sq->coord = ft_vect_multiplication(g_data->sq->coord, g_data->cam->dir);
			while (g_data->sq->tr->rank != -1)
				g_data->sq->tr = g_data->sq->tr->next;
			g_data->sq->tr = g_data->sq->tr->next;
			cmp = 0;
			while (cmp != 2)
			{
				g_data->sq->tr->p_1 = ft_vec_diff(g_data->sq->tr->p_1, abs_cam);
				g_data->sq->tr->p_1 = ft_vect_multiplication(g_data->sq->tr->p_1, g_data->cam->dir);
				g_data->sq->tr->p_2 = ft_vec_diff(g_data->sq->tr->p_2, abs_cam);
				g_data->sq->tr->p_2 = ft_vect_multiplication(g_data->sq->tr->p_2, g_data->cam->dir);
				g_data->sq->tr->p_3 = ft_vec_diff(g_data->sq->tr->p_3, abs_cam);
				g_data->sq->tr->p_3 = ft_vect_multiplication(g_data->sq->tr->p_3, g_data->cam->dir);
				g_data->sq->tr = g_data->sq->tr->next;
				cmp++;
			}
			if (g_data->sq->rank == -1)
				break ;
			g_data->sq = g_data->sq->next;
		}
	while (g_data->tr->rank != 0)
	{
		g_data->tr->p_1 = ft_vec_diff(g_data->tr->p_1, abs_cam);
		g_data->tr->p_1 = ft_vect_multiplication(g_data->tr->p_1, g_data->cam->dir);
		g_data->tr->p_2 = ft_vec_diff(g_data->tr->p_2, abs_cam);
		g_data->tr->p_2 = ft_vect_multiplication(g_data->tr->p_2, g_data->cam->dir);
		g_data->tr->p_3 = ft_vec_diff(g_data->tr->p_3, abs_cam);
		g_data->tr->p_3 = ft_vect_multiplication(g_data->tr->p_3, g_data->cam->dir);
		if (g_data->tr->rank == -1)
			break ;
		g_data->tr = g_data->tr->next;
	}
	while (g_data->cy->rank != 0)
	{
		g_data->cy->coord = ft_vec_diff(g_data->cy->coord, abs_cam);
		g_data->cy->coord = ft_vect_multiplication(g_data->cy->coord, g_data->cam->dir);
		if (g_data->cy->rank == -1)
			break ;
		g_data->cy = g_data->cy->next;
	}
	if (g_data->light->rank != 0)
	{
		while (g_data->light->rank != 0)
		{
			g_data->light->coord = ft_vec_diff(g_data->light->coord, abs_cam);
			g_data->light->coord = ft_vect_multiplication(g_data->light->coord, g_data->cam->dir);
			if (g_data->cy->rank == -1)
				break ;
			g_data->light = g_data->light->next;
		}
	}
	if (g_data->light->rank == 0)
	{
		g_data->light->color = g_data->ambience.color;
		g_data->light->ratio = g_data->ambience.ratio;
	}
	g_data->cam->coord.x = 1;
	g_data->cam->coord.y = 1;
	g_data->cam->coord.z = 1;
}
