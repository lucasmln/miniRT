/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:54:08 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/19 14:43:44 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int		ft_obj_is_plane_2(char *s, int i, double aux[3])
{
	g_data->pl->ratio_trans = 0;
	i = ft_get_color(aux, s, i);
	if (i == -1 || ft_set_ori(&g_data->pl->color, aux, 2) == -1)
		return (-1);
	while (s[i] == ' ')
		i++;
	if (s[i] == 'm')
		g_data->pl->spec = 1;
	else if (s[i] == 't')
	{
		g_data->pl->trans = 1;
		i++;
		while (s[i] == ' ')
			i++;
		if (!(s[i] <= '9' && s[i] >= '0') && s[i] != ' ')
			return (-1);
		g_data->pl->ratio_trans = ft_atod(&s[i]);
		i = ft_pass_double(s, i);
		g_data->pl->ratio_trans = (g_data->pl->ratio_trans == 0) ? 1 :
														g_data->pl->ratio_trans;
	}
	i = g_data->pl->spec == 1 ? i + 1 : i;
	if (s[i] != '\n')
		return (-1);
	return (i);
}

int		ft_obj_is_plane(char *s, int i)
{
	double				aux[3];
	static t_plane		*save_pl;

	if (g_data->pl->rank != 0)
	{
		if (!(g_data->pl->next = malloc(sizeof(t_plane))))
			ft_print_error(-1);
		g_data->pl->next->rank = g_data->pl->rank;
		g_data->pl = g_data->pl->next;
	}
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_coord(aux, s, i)) == -1)
		return (-1);
	ft_set_ori(&g_data->pl->coord, aux, 0);
	if ((i = ft_get_dir(aux, s, i)) == -1)
		return (-1);
	if (ft_set_ori(&g_data->pl->dir, aux, 1) == -1)
		return (-1);
	i = ft_obj_is_plane_2(s, i, aux);
	if (g_data->pl->rank == 0)
		save_pl = g_data->pl;
	g_data->pl->rank++;
	g_data->pl->next = save_pl;
	return (i);
}
