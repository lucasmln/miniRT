/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_leaks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:49:06 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/28 16:39:04 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void		ft_no_leaks(void)
{
	t_data		*tmp;

	if (!(tmp = malloc(sizeof(t_data) * 1)))
		ft_print_error(-1);
	if (g_data->sp->next)
		while (1)
		{
			tmp->sp = g_data->sp;
			tmp->check = g_data->sp->rank;
			g_data->sp = g_data->sp->next;
			free(tmp->sp);
			tmp->sp = NULL;
			if (tmp->check == -1)
				break ;
		}
	else
	{
		free(g_data->sp);
		g_data->sp = NULL;
	}
	if (g_data->pl->next)
		while (1)
		{
			tmp->pl = g_data->pl;
			tmp->check = g_data->pl->rank;
			g_data->pl = g_data->pl->next;
			free(tmp->pl);
			tmp->pl = NULL;
			if (tmp->check == -1)
				break ;
		}
	else
	{
		free(g_data->pl);
		g_data->pl = NULL;
	}
	if (g_data->tr->next)
		while (1)
		{
			tmp->tr = g_data->tr;
			tmp->check = g_data->tr->rank;
			g_data->tr = g_data->tr->next;
			free(tmp->tr);
			tmp->tr = NULL;
			if (tmp->check == -1)
				break ;
		}
	else
	{
		free(g_data->tr);
		g_data->tr = NULL;
	}
	if (g_data->cy->next)
		while (1)
		{
			tmp->cy = g_data->cy;
			tmp->check = g_data->cy->rank;
			g_data->cy = g_data->cy->next;
			free(tmp->cy);
			tmp->cy = NULL;
			if (tmp->check == -1)
				break ;
		}
	else
	{
		free(g_data->cy);
		g_data->cy = NULL;
	}
	if (g_data->sq->next)
		while (1)
		{
			tmp->sq = g_data->sq;
			tmp->check = g_data->sq->rank;
			g_data->sq = g_data->sq->next;
			free(tmp->sq->tr->next);
			free(tmp->sq->tr);
			free(tmp->sq);
			tmp->sq->tr->next = NULL;
			tmp->sq->tr = NULL;
			tmp->sq = NULL;
			if (tmp->check == -1)
				break ;
		}
	else
	{
		free(g_data->sq);
		g_data->sq = NULL;
	}
	if (g_data->cam->next)
		while (1)
		{
			tmp->cam = g_data->cam->next;
			tmp->check = g_data->cam->rank;
			free(g_data->cam);
			g_data->cam = NULL;
			g_data->cam = tmp->cam;
			if (tmp->check == -1)
				break ;
		}
	else
	{
		free(g_data->cam);
		g_data->cam = NULL;
	}
	if (g_data->light->next)
		while (1)
		{
			tmp->light = g_data->light;
			tmp->check = g_data->light->rank;
			g_data->light = g_data->light->next;
			free(tmp->light);
			tmp->light = NULL;
			if (tmp->check == -1)
				break ;
		}
	else
	{
		free(g_data->light);
		g_data->light = NULL;
	}
/*	if (g_data->image->next)
		while (1)
		{
			printf("img %d = %p\n", g_data->image->rank, g_data->image->ptr);
			tmp->image = g_data->image->next;
			tmp->check = g_data->image->rank;
			free(g_data->image->ptr);
			free(g_data->image->img);
			free(g_data->image);
			g_data->image->img = NULL;
			g_data->image->ptr = NULL;
			g_data->image = NULL;
			g_data->image = tmp->image;
			if (tmp->check == -1)
				break ;
		}
	else
	{
		free(g_data->image);
		g_data->image = NULL;
	}*/
	free(tmp);
	tmp = NULL;
	free(g_data->file);
	g_data->file = NULL;
	free(g_data);
	g_data = NULL;
}
