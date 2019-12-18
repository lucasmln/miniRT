/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_obj_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 09:03:50 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/18 15:18:32 by lmoulin          ###   ########.fr       */
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

int		ft_obj_is_sphere(t_data *data, char *s, int i)
{
	double	aux[3];
	static t_sphere *save_sp;

	if (data->sp->rank != 0)
	{
		if (!(data->sp->next = malloc(sizeof(t_sphere))))
			return (-1);
		data->sp->next->rank = data->sp->rank;
		data->sp = data->sp->next;
	}
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_coord(aux, s, i)) == -1)
		return (-1);
	ft_set_ori(&data->sp->coord, aux);
	while (s[i] == ' ')
		i++;
	data->sp->diameter = ft_atod(&s[i]);
	i = ft_pass_double(s, i);
	i = ft_get_color(aux, s, i);
	ft_set_ori(&data->sp->color, aux);
	while (s[i] == ' ')
		i++;
	if (s[i] == 'm')
	{
		i++;
		data->sp->spec = 1;
	}
	if (i == -1 || s[i] != '\n')
		return (-1);
	if (data->sp->rank == 0)
		save_sp = data->sp;
	data->sp->rank++;
	data->sp->next = save_sp;
	return (i);
}

int		ft_obj_is_plane(t_data *data, char *s, int i)
{
	double	aux[3];
	static t_plane *save_pl;

	if (data->pl->rank != 0)
	{
		if (!(data->pl->next = malloc(sizeof(t_plane))))
			return (-1);
		data->pl->next->rank = data->pl->rank;
		data->pl = data->pl->next;
	}
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_coord(aux, s, i)) == -1)
		return (-1);
	ft_set_ori(&data->pl->coord, aux);
	if ((i = ft_get_dir(aux, s, i)) == -1)
		return (-1);
		ft_set_ori(&data->pl->dir, aux);
	if ((i = ft_get_color(aux, s, i)) == -1)
		return (-1);
	ft_set_ori(&data->pl->color, aux);
	while (s[i] == ' ')
		i++;
	if (s[i] == 'm')
	{
		data->pl->spec = 1;
		i++;
	}
	if (s[i] != '\n')
		return (-1);
	if (data->pl->rank == 0)
		save_pl = data->pl;
	data->pl->rank++;
	data->pl->next = save_pl;
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
	data->sp->rank = -1;
	data->pl->rank = -1;
	data->sq->rank = -1;
	data->cy->rank = -1;
	data->cy->rank = -1;
	data->tr->rank = -1;
	return (i);
}


int		ft_check_file(t_data *data, char *s)
{
	int		i;

	i = 0;
	if (s[i] == 'R' || s[i] == 'A')
		if ((i = ft_ambience_and_res(data, s, i)) == -1)
			return (-1);
	while (s[i] == '\n')
		i++;
	if (s[i] == 'c' || s[i] == 'l')
		if ((i = ft_cam_and_light(data, s, i)) == -1)
			return (-1);
	while (s[i] == '\n')
		i++;
	if (ft_check_valid_obj(s, i) == 1)
		if ((i = ft_objet(data, s, i)) == -1)
			return (-1);
	return (0);
}
