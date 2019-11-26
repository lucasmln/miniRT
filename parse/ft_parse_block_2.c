/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_block_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:07:30 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/26 16:13:11 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../libft/libft.h"

int		ft_get_cam(t_data *data, char *s, int i)
{
	int		k;
	double	aux[3];

	while (s[i] == ' ')
		i++;
	if ((s[i] < '0' && s[i] > '9' && s[i] != '-') ||
		(s[i] == '-' && s[i + 1] > '9' && s[i + 1] < '0'))
		return (-1);
	i = ft_get_coord(aux, s, i);
	ft_set_ori(&data->cam->coord, aux);
	if (i == -1)
		return (i);
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_dir(aux, (const char *)s, i)) == -1)
		return (-1);
	ft_set_ori(&data->cam->dir, aux);
//	k = -1;
//	while (++k <= 2)
//		if ((data->cam->dir[k] < -1.0 || data->cam->dir[k] > 1.0) || i == -1)
//			return (-1);
	while (s[i] == ' ')
		i++;
	data->cam->fov = ft_atoi(&s[i]);
	i += ft_strlen_nb(data->cam->fov);
	return ((s[i] == '\n' ? i + 1 : -1));
}

int		ft_get_light(t_data *data, char *s, int i)
{
	int		k;
	double	aux[3];

	k = -1;
	while (s[i] == ' ')
		i++;
	i = ft_get_coord(aux, s, i);
	ft_set_ori(&data->light->coord, aux);
	if (i == -1)
		return (-1);
	while (s[i] == ' ')
		i++;
	data->light->ratio = ft_atod(&s[i]);
	i = ft_pass_double(s, i);
	if ((data->light->ratio > 1.0 && data->light->ratio < 0.0) || i == -1)
		return (-1);
	i = ft_get_color(aux, s, i);
	ft_set_ori(&data->light->color, aux);
	if (i == -1 || s[i] != '\n')
		return (-1);
	i++;
	return (i);
}

int		ft_cam_and_light(t_data *data, char *s, int i)
{
	t_cam	*save_cam;
	t_light	*save_light;

	while (i != -1 && (s[i] == 'l' || s[i] == 'c'))
	{
		if (s[i] == 'c')
		{
			if (data->cam->rank != 0)
			{
				if (!(data->cam->next = malloc(sizeof(t_cam))))
					return (-1);
				data->cam->next->rank = data->cam->rank;
				data->cam = data->cam->next;
		//		data->cam->next = save_cam;
			}
			i = ft_get_cam(data, s, i + 1);
			if (data->cam->rank == 0)
				save_cam = data->cam;
			data->cam->rank++;
		}
		else if (s[i] == 'l')
		{
			if (data->light->rank != 0)
			{
				if (!(data->light->next = malloc(sizeof(t_cam))))
					return (-1);
				data->light->next->rank = data->light->rank;
				data->light = data->light->next;
		//		data->light->next = save_light;
			}
			i = ft_get_light(data, s, i + 1);
			if (data->light->rank == 0)
				save_light = data->light;
			data->light->rank++;
		}
	}
	data->light->next = save_light;
	data->light = save_light;
	data->cam->next = save_cam;
	data->cam = save_cam;
	return (i);
}
