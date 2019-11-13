/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:08:10 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/13 15:57:44 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft/libft.h"
#include "miniRT_struct.h"
#include "miniRT.h"

int		ft_obj_is_square(t_data *data, char *s, int i)
{
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_coord(data->square->coord, s, i)) == -1)
		return (-1);
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_dir(data->square->dir, s, i)) == -1)
		return (-1);
	while (s[i] == ' ')
		i++;
	data->square->height = ft_atod(&s[i]);
	while (s[i] <= '9' && s[i] >= '0')
		i++;
	if (s[i] == '.')
		i++;
	while (s[i] <= '9' && s[i] >= '0')
		i++;
	if ((i = ft_get_color(data->square->color, s, i)) == -1)
		return (-1);
	if (s[i] != '\n')
		return (-1);
	if (s[i] == '\0')
		return (i);
	return (i);
}

int		ft_obj_is_cylinder(t_data *data, char *s, int i)
{
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_coord(data->cylinder->coord, s, i)) == -1)
		return (-1);
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_dir(data->cylinder->dir, s, i)) == -1)
		return (-1);
	while (s[i] == ' ')
		i++;
	data->cylinder->diameter = ft_atod(&s[i]);
	i = ft_pass_double(s, i);
	while (s[i] == ' ')
		i++;
	data->cylinder->height = ft_atod(&s[i]);
	i = ft_pass_double(s, i);
	i = ft_get_color(data->cylinder->color, s, i);
	if (i == -1 || s[i] != '\n')
		return (-1);
	return (i);
}

int		ft_obj_is_triangle(t_data *data, char *s, int i)
{
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_coord(data->triangle->coord_one, s, i)) == -1)
		return (-1);
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_coord(data->triangle->coord_two, s, i)) == -1)
		return (-1);
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_coord(data->triangle->coord_three, s, i)) == -1)
		return (-1);
	i = ft_get_color(data->triangle->color, s, i);
	if (i == -1 || s[i] != '\n')
		return (-1);
	return (i);
}
