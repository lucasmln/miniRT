/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_block_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:07:30 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/25 13:50:49 by lmoulin          ###   ########.fr       */
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
	while (i != -1 && (s[i] == 'l' || s[i] == 'c'))
	{
		if (s[i] == 'c')
		{
			if (!(data->cam = malloc(sizeof(t_cam) * 1)))
				return (-1); 
			i = ft_get_cam(data, s, i + 1);
		}
		else if (s[i] == 'l')
			i = ft_get_light(data, s, i + 1);
	}
	return (i);
}
