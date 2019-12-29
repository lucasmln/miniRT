/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:44:36 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/17 20:57:05 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	ft_new_img(void)
{
	t_image	*img;

	if (!(img = malloc(sizeof(t_image))))
		ft_print_error(-1);
	img->img = mlx_new_image(g_mlx.ptr, g_data->render[0], g_data->render[1]);
	if (img->img == NULL)
		ft_print_error(-8);
	img->ptr = mlx_get_data_addr(img->img, &img->bpp, &img->stride,
				&img->endian);
	img->bpp /= 8;
	g_data->image = img;
}

void	ft_put_pixel_to_img(int x, int y, long color)
{
	if (x < 0 || x >= g_data->render[0] || y < 0 || y >= g_data->render[1])
		return ;
	*(int *)(g_data->image->ptr + ((x + y * g_data->render[0]) *
		g_data->image->bpp)) = color;
}
