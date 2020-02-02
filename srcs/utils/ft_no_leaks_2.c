/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_leaks_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:27:19 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/30 15:34:16 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void		ft_no_leaks_7(t_data *tmp)
{
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
}

void		ft_no_leaks_6(t_data *tmp)
{
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
	ft_no_leaks_7(tmp);
}
