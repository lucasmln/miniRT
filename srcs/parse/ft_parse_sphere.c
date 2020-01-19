/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:51:51 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/19 14:41:07 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int		ft_obj_is_sphere_2(char *s, int i, double aux[3])
{
	i = ft_pass_double(s, i);
	i = ft_get_color(aux, s, i);
	ft_set_ori(&g_data->sp->color, aux, 0);
	while (s[i] == ' ')
		i++;
	if (s[i] == 'm')
		g_data->sp->spec = 1;
	else if (s[i] == 't')
	{
		g_data->sp->trans = 1;
		i++;
		while (s[i] == ' ')
			i++;
		if (!(s[i] <= '9' && s[i] >= '0') && s[i] != ' ' && s[i] != '\n')
			return (-1);
		g_data->sp->ratio_trans = ft_atod(&s[i]);
		i = ft_pass_double(s, i);
		g_data->sp->ratio_trans = (g_data->sp->ratio_trans == 0) ? 1 :
														g_data->sp->ratio_trans;
	}
	i = g_data->sp->spec == 1 ? i + 1 : i;
	if (i == -1 || s[i] != '\n')
		return (-1);
	return (i);
}

int		ft_obj_is_sphere(char *s, int i)
{
	double				aux[3];
	static t_sphere		*save_sp;

	if (g_data->sp->rank != 0)
	{
		if (!(g_data->sp->next = malloc(sizeof(t_sphere))))
			ft_print_error(-1);
		g_data->sp->next->rank = g_data->sp->rank;
		g_data->sp = g_data->sp->next;
	}
	g_data->sp->ratio_trans = 0;
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_coord(aux, s, i)) == -1)
		return (-1);
	ft_set_ori(&g_data->sp->coord, aux, 0);
	while (s[i] == ' ')
		i++;
	g_data->sp->diameter = ft_atod(&s[i]);
	i = ft_obj_is_sphere_2(s, i, aux);
	if (g_data->sp->rank == 0)
		save_sp = g_data->sp;
	g_data->sp->rank++;
	g_data->sp->next = save_sp;
	return (i);
}

int		ft_objet(char *s, int i)
{
	while (s[i] && ft_check_valid_obj(s, i))
	{
		if (ft_strncmp(&s[i], "sp", 2) == 0)
			i = ft_obj_is_sphere(s, i + 2);
		else if (ft_strncmp(&s[i], "pl", 2) == 0)
			i = ft_obj_is_plane(s, i + 2);
		else if (ft_strncmp(&s[i], "sq", 2) == 0)
			i = ft_obj_is_square(s, i + 2);
		else if (ft_strncmp(&s[i], "cy", 2) == 0)
			i = ft_obj_is_cylinder(s, i + 2);
		else if (ft_strncmp(&s[i], "tr", 2) == 0)
			i = ft_obj_is_triangle(s, i + 2);
		else
			return (-1);
		if (i == -1 || s[i] == '\0')
			break ;
		i++;
	}
	g_data->sp->rank = -1;
	g_data->pl->rank = -1;
	g_data->sq->rank = -1;
	g_data->cy->rank = -1;
	g_data->cy->rank = -1;
	g_data->tr->rank = -1;
	return (i);
}
