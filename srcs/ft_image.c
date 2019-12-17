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

void	ft_new_img(t_data *data)
{
	t_image	*img;

	if (!(img = malloc(sizeof(t_image))))
		return ;
	img->img = mlx_new_image(g_mlx.ptr, data->render[0], data->render[1]);
	if (img->img == NULL)
		return ;
	img->ptr = mlx_get_data_addr(img->img, &img->bpp, &img->stride,
				&img->endian);
	img->bpp /= 8;
	data->image = img;
}

void	ft_put_pixel_to_img(int x, int y, long color, t_data *data)
{
	if (x < 0 || x >= data->render[0] || y < 0 || y >= data->render[1])
		return ;
	*(int *)(data->image->ptr + ((x + y * data->render[0]) *
		data->image->bpp)) = color;
}
