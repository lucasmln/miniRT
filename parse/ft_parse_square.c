/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_square.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:51:13 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/16 14:51:16 by lmoulin          ###   ########.fr       */
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
