/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:54:20 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/16 14:54:46 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int		ft_obj_is_cylinder_3(char *s, int i, double aux[3])
{
	g_data->cy->trans = 1;
	while (s[++i] == ' ')
		;
	if (!(s[i] <= '9' && s[i] >= '0') && s[i] != ' ' && s[i] != '\n')
		return (-1);
	g_data->cy->ratio_trans = ft_atod(&s[i]);
	i = ft_pass_double(s, i);
	g_data->cy->ratio_trans = (g_data->cy->ratio_trans == 0) ? 1 :
													g_data->cy->ratio_trans;
	return (i);
}

int		ft_obj_is_cylinder_2(char *s, int i, double aux[3])
{
	if (g_data->cy->rank != 0)
	{
		if (!(g_data->cy->next = malloc(sizeof(t_cylinder))))
			ft_print_error(-1);
		g_data->cy->next->rank = g_data->cy->rank;
		g_data->cy = g_data->cy->next;
	}
	while (s[i] == ' ')
		i++;
	i = ft_get_coord(aux, s, i);
	ft_set_ori(&g_data->cy->coord, aux, 0);
	while (i != -1 && s[i] == ' ')
		i++;
	if (i == -1 || (i = ft_get_dir(aux, s, i)) == -1)
		return (-1);
	if (ft_set_ori(&g_data->cy->dir, aux, 1) == -1)
		return (-1);
	while (s[i] == ' ')
		i++;
	g_data->cy->diameter = ft_atod(&s[i]);
	i = ft_pass_double(s, i);
	while (s[i] == ' ')
		i++;
	g_data->cy->height = ft_atod(&s[i]);
	return (i);
}

int		ft_obj_is_cylinder(char *s, int i)
{
	double				aux[3];
	static t_cylinder	*save_cy;

	i = ft_obj_is_cylinder_2(s, i, aux);
	i = ft_pass_double(s, i);
	i = ft_get_color(aux, s, i);
	if (ft_set_ori(&g_data->cy->color, aux, 2) == -1)
		return (-1);
	while (s[i] == ' ')
		i++;
	if (s[i] == 'm')
		g_data->cy->spec = 1;
	else if (s[i] == 't')
		i = ft_obj_is_cylinder_3(s, i, aux);
	if (i == -1 || s[i] != '\n')
		return (-1);
	if (g_data->cy->rank == 0)
		save_cy = g_data->cy;
	g_data->cy->rank++;
	g_data->cy->next = save_cy;
	return (i);
}
