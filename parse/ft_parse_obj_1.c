/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_obj_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 09:03:50 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/30 17:38:48 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../inc/minirt.h"

int		ft_check_valid_obj(char *s, int i)
{
	if (ft_strncmp(&s[i], "pl", 2) == 0 || ft_strncmp(&s[i], "sp", 2) == 0 ||
	ft_strncmp(&s[i], "sq", 2) == 0 || ft_strncmp(&s[i], "cy", 2) == 0 ||
	ft_strncmp(&s[i], "tr", 2) == 0)
		return (1);
	return (0);
}

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
		if (i == -1 || s[i] == '\0')
			break ;
		i++;
	}
	if (i == -1)
		return (-1);
	g_data->sp->rank = -1;
	g_data->pl->rank = -1;
	g_data->sq->rank = -1;
	g_data->cy->rank = -1;
	g_data->cy->rank = -1;
	g_data->tr->rank = -1;
	return (i);
}

int		ft_check_file(char *s)
{
	int		i;

	i = 0;
	if (s[i] == 'R' || s[i] == 'A')
		if ((i = ft_ambience_and_res(s, i)) == -1)
			return (-1);
	while (s[i] == '\n')
		i++;
	if (s[i] == 'c' || s[i] == 'l')
		if ((i = ft_cam_and_light(s, i)) == -1)
			return (-1);
	while (s[i] == '\n')
		i++;
	if (ft_check_valid_obj(s, i) == 1)
		if ((i = ft_objet(s, i)) == -1)
			return (-1);
	return (0);
}
