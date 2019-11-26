/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:08:10 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/26 16:24:15 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../libft/libft.h"
#include "../inc/minirt.h"

int		ft_obj_is_square(t_data *data, char *s, int i)
{
	double	aux[3];
	static t_square *save_sq;

	if (data->sq->rank != 0)
	{
		if (!(data->sq->next = malloc(sizeof(t_square))))
			return (-1);
		data->sq->next->rank = data->sq->rank;
		data->sq = data->sq->next;
	}
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_coord(aux, s, i)) == -1)
		return (-1);
	ft_set_ori(&data->sq->coord, aux);
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_dir(aux, s, i)) == -1)
		return (-1);
	ft_set_ori(&data->sq->dir, aux);
	while (s[i] == ' ')
		i++;
	data->sq->height = ft_atod(&s[i]);
	while (s[i] <= '9' && s[i] >= '0')
		i++;
	if (s[i] == '.')
		i++;
	while (s[i] <= '9' && s[i] >= '0')
		i++;
	if ((i = ft_get_color(aux, s, i)) == -1)
		return (-1);
	ft_set_ori(&data->sq->color, aux);
	if (s[i] != '\n')
		return (-1);
	if (data->sq->rank == 0)
		save_sq = data->sq;
	data->sq->rank++;
	data->sq->next = save_sq;
	return (i);
}

int		ft_obj_is_cylinder(t_data *data, char *s, int i)
{
	double	aux[3];
	static t_cylinder *save_cy;

	if (data->cy->rank != 0)
	{
		if (!(data->cy->next = malloc(sizeof(t_cylinder))))
			return (-1);
		data->cy->next->rank = data->cy->rank;
		data->cy = data->cy->next;
	}
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_coord(aux, s, i)) == -1)
		return (-1);
	ft_set_ori(&data->cy->coord, aux);
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_dir(aux, s, i)) == -1)
		return (-1);
	ft_set_ori(&data->cy->dir, aux);
	while (s[i] == ' ')
		i++;
	data->cy->diameter = ft_atod(&s[i]);
	i = ft_pass_double(s, i);
	while (s[i] == ' ')
		i++;
	data->cy->height = ft_atod(&s[i]);
	i = ft_pass_double(s, i);
	i = ft_get_color(aux, s, i);
	ft_set_ori(&data->cy->color, aux);
	if (i == -1 || s[i] != '\n')
		return (-1);
	if (data->cy->rank == 0)
		save_cy = data->cy;
	data->cy->rank++;
	data->cy->next = save_cy;
	return (i);
}

int		ft_obj_is_triangle(t_data *data, char *s, int i)
{
	double	aux[3];
	static t_triangle *save_tr;

	if (data->tr->rank != 0)
	{
		if (!(data->tr->next = malloc(sizeof(t_triangle))))
			return (-1);
		data->tr->next->rank = data->tr->rank;
		data->tr = data->tr->next;
	}
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_coord(aux, s, i)) == -1)
		return (-1);
	ft_set_ori(&data->tr->p_1, aux);
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_coord(aux, s, i)) == -1)
		return (-1);
	ft_set_ori(&data->tr->p_2, aux);
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_coord(aux, s, i)) == -1)
		return (-1);
	ft_set_ori(&data->tr->p_3, aux);
	i = ft_get_color(aux, s, i);
	ft_set_ori(&data->tr->color, aux);
	if (i == -1 || s[i] != '\n')
		return (-1);
	if (data->tr->rank == 0)
		save_tr = data->tr;
	data->tr->rank++;
	data->tr->next = save_tr;
	return (i);
}
