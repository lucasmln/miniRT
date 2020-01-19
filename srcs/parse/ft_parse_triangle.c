/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_triangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:50:15 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/19 14:41:23 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int		ft_obj_is_triangle_3(char *s, int i)
{
	g_data->tr->trans = 1;
	i++;
	while (s[i] == ' ')
		i++;
	if ((s[i] > '9' || s[i] < '0') && s[i] != ' ' && s[i] != '\n')
		return (-1);
	g_data->tr->ratio_trans = ft_atod(&s[i]);
	i = ft_pass_double(s, i);
	g_data->tr->ratio_trans = (g_data->tr->ratio_trans == 0) ? 1 :
														g_data->tr->ratio_trans;
	return (i);
}

int		ft_obj_is_triangle_2(char *s, int i, double aux[3])
{
	if (g_data->tr->rank != 0)
	{
		if (!(g_data->tr->next = malloc(sizeof(t_triangle))))
			ft_print_error(-1);
		g_data->tr->next->rank = g_data->tr->rank;
		g_data->tr = g_data->tr->next;
	}
	g_data->tr->ratio_trans = 0;
	while (s[i] == ' ')
		i++;
	i = ft_get_coord(aux, s, i);
	ft_set_ori(&g_data->tr->p_1, aux, 0);
	while (i != -1 && s[i] == ' ')
		i++;
	i = ft_get_coord(aux, s, i);
	ft_set_ori(&g_data->tr->p_2, aux, 0);
	while (i != -1 && s[i] == ' ')
		i++;
	if (i == -1 || (i = ft_get_coord(aux, s, i)) == -1)
		return (-1);
	ft_set_ori(&g_data->tr->p_3, aux, 0);
	i = ft_get_color(aux, s, i);
	if (ft_set_ori(&g_data->tr->color, aux, 2) == -1)
		return (-1);
	return (i);
}

int		ft_obj_is_triangle(char *s, int i)
{
	double				aux[3];
	static t_triangle	*save_tr;

	i = ft_obj_is_triangle_2(s, i, aux);
	while (s[i] == ' ')
		i++;
	if (s[i] == 'm')
		g_data->tr->spec = 1;
	else if (s[i] == 't')
		i = ft_obj_is_triangle_3(s, i);
	if ((i = g_data->tr->spec == 1 && i != -1 ? i + 1 : i) == -1 || s[i] != 10)
		return (-1);
	if (g_data->tr->rank == 0)
		save_tr = g_data->tr;
	g_data->tr->rank++;
	g_data->tr->next = save_tr;
	return (i);
}
