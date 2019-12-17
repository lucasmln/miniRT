/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:20:57 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/17 20:16:04 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int		esc_key(int key, void *p)
{
	if (key == ESC_KEY)
	{
		mlx_destroy_window(g_mlx.ptr, g_mlx.win);
		exit(0);
	}
	return (0);
}

int		close_window(int button, int x, int y, void *p)
{
	mlx_destroy_window(g_mlx.ptr, g_mlx.win);
	exit(0);
}

int		get_key(int key, void *p)
{
	if (key == ESC_KEY)
	{
		mlx_destroy_window(g_mlx.ptr, g_mlx.win);
		exit(0);
	}
	return (0);
}
