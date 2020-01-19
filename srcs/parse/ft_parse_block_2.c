/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_block_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:07:30 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/19 15:09:44 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int		ft_get_cam(char *s, int i)
{
	double	aux[3];

	while (s[i] == ' ')
		i++;
	if ((s[i] < '0' && s[i] > '9' && s[i] != '-') ||
		(s[i] == '-' && s[i + 1] > '9' && s[i + 1] < '0'))
		return (-1);
	i = ft_get_coord(aux, s, i);
	ft_set_ori(&g_data->cam->coord, aux, 0);
	if (i == -1)
		return (i);
	while (s[i] == ' ')
		i++;
	if ((i = ft_get_dir(aux, (const char *)s, i)) == -1)
		return (-1);
	if (ft_set_ori(&g_data->cam->dir, aux, 1) == -1)
		return (-1);
	while (s[i] == ' ')
		i++;
	g_data->cam->fov = ft_atoi(&s[i]);
	i += ft_strlen_nb(g_data->cam->fov);
	return ((s[i] == '\n' ? i + 1 : -1));
}

int		ft_get_light(char *s, int i)
{
	int		k;
	double	aux[3];

	k = -1;
	while (s[i] == ' ')
		i++;
	i = ft_get_coord(aux, s, i);
	ft_set_ori(&g_data->light->coord, aux, 0);
	if (i == -1)
		return (-1);
	while (s[i] == ' ')
		i++;
	g_data->light->ratio = ft_atod(&s[i]);
	i = ft_pass_double(s, i);
	if ((g_data->light->ratio > 1.0 && g_data->light->ratio < 0.0) || i == -1)
		return (-1);
	i = ft_get_color(aux, s, i);
	if (ft_set_ori(&g_data->light->color, aux, 2) == -1)
		return (-1);
	if (i == -1 || s[i] != '\n')
		return (-1);
	i++;
	return (i);
}

int		ft_is_cam(char *s, int i, t_cam **save_cam)
{
	if (g_data->cam->rank != 0)
	{
		if (!(g_data->cam->next = malloc(sizeof(t_cam))))
			ft_print_error(-1);
		g_data->cam->next->rank = g_data->cam->rank;
		g_data->cam = g_data->cam->next;
	}
	i = ft_get_cam(s, i + 1);
	if (g_data->cam->rank == 0)
		*save_cam = g_data->cam;
	g_data->cam->rank++;
	return (i);
}

int		ft_is_light(char *s, int i, t_light **save_light)
{
	if (g_data->light->rank != 0)
	{
		if (!(g_data->light->next = malloc(sizeof(t_cam))))
			ft_print_error(-1);
		g_data->light->next->rank = g_data->light->rank;
		g_data->light = g_data->light->next;
	}
	i = ft_get_light(s, i + 1);
	if (g_data->light->rank == 0)
		*save_light = g_data->light;
	g_data->light->rank++;
	return (i);
}

int		ft_cam_and_light(char *s, int i)
{
	t_cam	*save_cam;
	t_light	*save_light;

	while (i != -1 && (s[i] == 'l' || s[i] == 'c'))
	{
		if (s[i] == 'c')
			i = ft_is_cam(s, i, &save_cam);
		else if (s[i] == 'l')
			i = ft_is_light(s, i, &save_light);
	}
	if (g_data->light->rank != 0)
	{
		g_data->light->next = save_light;
		g_data->light->rank = -1;
		g_data->light = save_light;
	}
	if (g_data->cam->rank != 0)
	{
		g_data->cam->next = save_cam;
		g_data->cam->rank = -1;
		g_data->cam = save_cam;
	}
	return (i);
}
