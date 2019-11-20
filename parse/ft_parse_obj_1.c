/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_obj_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 09:03:50 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/20 15:15:55 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../inc/miniRT_struct.h"
#include "../inc/miniRT.h"
#include <stdio.h>

int		ft_check_valid_obj(char *s, int i)
{
	if (ft_strncmp(&s[i], "pl", 2) == 0 || ft_strncmp(&s[i], "sp", 2) == 0 ||
	ft_strncmp(&s[i], "sq", 2) == 0 || ft_strncmp(&s[i], "cy", 2) == 0 ||
	ft_strncmp(&s[i], "tr", 2) == 0)
		return (1);
	return (0);
}

int		ft_obj_is_sphere(t_data *data, char *s, int i)
{
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_coord(data->sphere->coord, s, i)) == -1)
		return (-1);
	while (s[i] == ' ')
		i++;
	data->sphere->diameter = ft_atod(&s[i]);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] == '.')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	while (s[i] == ' ')
		i++;
	i = ft_get_color(data->sphere->color, s, i);
	if (i == -1 || s[i] != '\n')
		return (-1);
	return (i);
}

int		ft_obj_is_plane(t_data *data, char *s, int i)
{
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_coord(data->plane->coord, s, i)) == -1)
		return (-1);
	if ((i = ft_get_dir(data->plane->dir, s, i)) == -1)
		return (-1);
	if ((i = ft_get_color(data->plane->color, s, i)) == -1)
		return (-1);
	if (s[i] != '\n')
		return (-1);
	return (i);
}

int		ft_objet(t_data *data, char *s, int i)
{
	while (s[i] && ft_check_valid_obj(s, i))
	{
		if (ft_strncmp(&s[i], "sp", 2) == 0)
			i = ft_obj_is_sphere(data, s, i + 2);
		else if (ft_strncmp(&s[i], "pl", 2) == 0)
			i = ft_obj_is_plane(data, s, i + 2);
		else if (ft_strncmp(&s[i], "sq", 2) == 0)
			i = ft_obj_is_square(data, s, i + 2);
		else if (ft_strncmp(&s[i], "cy", 2) == 0)
			i = ft_obj_is_cylinder(data, s, i + 2);
		else if (ft_strncmp(&s[i], "tr", 2) == 0)
			i = ft_obj_is_triangle(data, s, i + 2);
		if (i == -1 || s[i] == '\0')
			break;
		i++;
	}
	if (i == -1)
		return (-1);
	return (i);
}


int		ft_check_file(t_data *data, char *s)
{
	int		i;

	i = 0;
	if (s[i] == 'R' || s[i] == 'A')
		if ((i = ft_ambience_and_res(data, s, i)) == -1)
		{
			write(1, "error ambience or render\n", ft_strlen("error ambience or render\n"));
			return (-1);
		}
	while (s[i] == '\n')
		i++;
	if (s[i] == 'c' || s[i] == 'l')
		if ((i = ft_cam_and_light(data, s, i)) == -1)
		{
			write(1, "error cam or light\n", ft_strlen("error cam or light\n"));
			return (-1);
		}
	while (s[i] == '\n')
		i++;
	if (ft_check_valid_obj(s, i) == 1)
		if ((i = ft_objet(data, s, i)) == -1)
		{
			write(1, "error obj\n", ft_strlen("error obj\n"));
			return (-1);
		}
	return (0);
}
