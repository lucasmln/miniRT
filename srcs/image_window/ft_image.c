/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:44:36 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/28 16:33:51 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	ft_create_all_img(void)
{
	static t_image	*save_img;

	while (g_data->cam->rank != -1)
		g_data->cam = g_data->cam->next;
	g_data->cam = g_data->cam->next;
	while (1)
	{
		if (g_data->image->rank != 0)
		{
			if (!(g_data->image->next = malloc(sizeof(t_image))))
				ft_print_error(-1);
			g_data->image->next->rank = g_data->image->rank;
			g_data->image = g_data->image->next;
		}
		ft_new_img(g_data);
		ft_draw(g_data);
		if (g_data->image->rank == 0)
			save_img = g_data->image;
		g_data->image->rank++;
		if (g_data->cam->rank == -1)
			break ;
		g_data->cam = g_data->cam->next;
	}
	g_data->image->rank = -1;
	g_data->image->next = save_img;
}

void	ft_new_img(void)
{
	g_data->image->img = mlx_new_image(g_mlx.ptr, g_data->render[0],
															g_data->render[1]);
	if (g_data->image->img == NULL)
		ft_print_error(-8);
	g_data->image->ptr = mlx_get_data_addr(g_data->image->img,
									&g_data->image->bpp, &g_data->image->stride,
														&g_data->image->endian);
	g_data->image->bpp /= 8;
}

void	ft_put_pixel_to_img(int x, int y, long color)
{
	if (x < 0 || x >= g_data->render[0] || y < 0 || y >= g_data->render[1])
		return ;
	*(int *)(g_data->image->ptr + ((x + y * g_data->render[0]) *
		g_data->image->bpp)) = color;
}

void	ft_change_cam(int key)
{
	int		pos;

	pos = g_data->image->rank;
	if (key == 123)
		while (g_data->image->next->rank != pos)
			g_data->image = g_data->image->next;
	else if (key == 124)
		g_data->image = g_data->image->next;
	mlx_put_image_to_window(g_mlx.ptr, g_mlx.win, g_data->image->img, 0, 0);
}
