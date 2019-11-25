/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:08:10 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/25 14:09:32 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../libft/libft.h"
#include "../inc/minirt.h"

int		ft_obj_is_square(t_data *data, char *s, int i)
{
	double	aux[3];

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
	if (s[i] == '\0')
		return (i);
	return (i);
}

int		ft_obj_is_cylinder(t_data *data, char *s, int i)
{
	double	aux[3];

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
	return (i);
}

int		ft_obj_is_triangle(t_data *data, char *s, int i)
{
	double	aux[3];

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
	return (i);
}
