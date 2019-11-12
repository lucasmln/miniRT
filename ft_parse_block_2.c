/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_block_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:07:30 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/12 18:13:46 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "miniRT_struct.h"
#include "libft/libft.h"

int		ft_get_cam(t_data *data, char *s, int i)
{
	int		k;

	while (s[i] == ' ')
		i++;
	if ((s[i] < '0' && s[i] > '9' && s[i] != '-') ||
		(s[i] == '-' && s[i + 1] > '9' && s[i + 1] < '0'))
		return (-1);
	i = ft_get_coord(data->cam->coord, s, i);
	if (i == -1)
		return (i);
	while (s[i] == ' ')
		i++;
	i = ft_get_coord(data->cam->dir, s, i);
	k = 0;
	while (k <= 2)
		if ((data->cam->dir[k] < -1.0 || data->cam->dir[k] > 1.0) || i == -1)
			return (-1);
	while (s[i] == ' ')
		i++;
	data->cam->fov = ft_atoi(&s[i]);
	return ((s[i] == '\n' ? i + 1 : -1));
}

int		ft_get_light(t_data *data, char *s, int i)
{
	while (s[i] == ' ')
		i++;
	i = ft_get_coord(data->light->coord, s, i);
	if (i == -1)
		return (-1);
	while (s[i] == ' ')
		i++;
	data->light->ratio = ft_atod(&s[i]);
	if ((data->light->ratio > 1.0 && data->light->ratio < 0.0) || i == -1)
		return (-1);
	i = ft_get_color(data->light->color, s, i);
	if (i == -1 || s[i] != '\n')
		return (-1);
	i++;
	return (i);
}

int		ft_cam_and_light(t_data *data, char *s, int i)
{
	while (i != -1 && (s[i] == 'l' || s[i] == 'c'))
	{
		if (s[i] == 'c')
			i = ft_get_cam(data, s, i + 1);
		else if (s[i] == 'l')
			i = ft_get_light(data, s, i + 1);
	}
	return (i);
}

