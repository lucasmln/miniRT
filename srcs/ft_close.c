/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:20:57 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/04 20:12:45 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int		esc_key(int key, void *p)
{
	if (key == ESC_KEY)
	{
		mlx_destroy_window(g_mlx.ptr, g_mlx.win);
		exit (0);
	}
	return (0);
}

int		close_window(int button,int x,int y, void *p)
{
	mlx_destroy_window(g_mlx.ptr, g_mlx.win);
	exit(0);
}

int		get_key(int key, void *p)
{
	int	up = 1;

	if (key == ESC_KEY)
	{
		mlx_destroy_window(g_mlx.ptr, g_mlx.win);
		exit (0);
	}
	if (key == 0x7e)
	{
		while (data->light->coord.y <= 0)
		{
			if (data->light->coord.z < data->sp->coord.z)
				up = -1;
			data->light->coord.z -= 1;
			data->light->coord.y -= up;
			ft_put_scene();
		}
	}
	if (key == 0x7d)
	{
		data->sp->coord.z += 5;
		ft_put_scene();
	}
	if (key == 0x7c)
	{
		data->sp->coord.x += 5;
		ft_put_scene();
	}
	if (key == 0x7b)
	{
		data->sp->coord.x -= 5;
		ft_put_scene();
	}
	return (0);
}
