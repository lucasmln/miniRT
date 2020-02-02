/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_leaks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:49:06 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/30 15:34:31 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void		ft_no_leaks_5(t_data *tmp)
{
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
}

void		ft_no_leaks_4(t_data *tmp)
{
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
	ft_no_leaks_5(tmp);
}

void		ft_no_leaks_3(t_data *tmp)
{
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
	ft_no_leaks_4(tmp);
}

void		ft_no_leaks_2(t_data *tmp)
{
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
	ft_no_leaks_3(tmp);
}

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
	free(tmp);
	tmp = NULL;
	free(g_data->file);
	g_data->file = NULL;
}
