/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:08:10 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/30 19:10:57 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../inc/minirt.h"

int		ft_obj_is_square_3(char *s, int i)
{
	if (s[i] == 'm')
		g_data->sq->spec = 1;
	else if (s[i] == 't')
	{
		g_data->sq->trans = 1;
		while (s[++i] == ' ')
			;
		if (!(s[i] <= '9' && s[i] >= '0') && s[i] != ' ' && s[i] != '\n')
			return (-1);
		g_data->sq->ratio_trans = ft_atod(&s[i]);
		i = ft_pass_double(s, i);
		g_data->sq->ratio_trans = (g_data->sq->ratio_trans == 0) ? 1 :
														g_data->sq->ratio_trans;
	}
	return (i);
}

int		ft_obj_is_square_2(char *s, int i, double aux[3])
{
	if (g_data->sq->rank != 0)
	{
		if (!(g_data->sq->next = malloc(sizeof(t_square))))
			ft_print_error(-1);
		g_data->sq->next->rank = g_data->sq->rank;
		g_data->sq = g_data->sq->next;
	}
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_coord(aux, s, i)) == -1)
		return (-1);
	ft_set_ori(&g_data->sq->coord, aux, 0);
	while (s[i] == ' ')
		i++;
	i = ft_get_dir(aux, s, i);
	if (i == -1 || ft_set_ori(&g_data->sq->dir, aux, 1) == -1)
		return (-1);
	while (s[i] == ' ')
		i++;
	g_data->sq->height = ft_atod(&s[i]);
	i = ft_pass_double(s, i);
	i = ft_get_color(aux, s, i);
	if (i == -1 || ft_set_ori(&g_data->sq->color, aux, 2) == -1)
		return (-1);
	return (i);
}

int		ft_obj_is_square(char *s, int i)
{
	double				aux[3];
	static t_square		*save_sq;

	g_data->sq->ratio_trans = 0;
	i = ft_obj_is_square_2(s, i, aux);
	while (s[i] == ' ')
		i++;
	i = ft_obj_is_square_3(s, i);
	i = g_data->sq->spec == 1 && i != -1 ? i + 1 : i;
	if (s[i] != '\n' || ft_init_tr_in_sq(g_data->sq) == -1)
		return (-1);
	ft_create_square_point(g_data->sq);
	if (g_data->sq->rank == 0)
		save_sq = g_data->sq;
	g_data->sq->rank++;
	g_data->sq->next = save_sq;
	return (i);
}

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
