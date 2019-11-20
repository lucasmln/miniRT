/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:44:36 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/20 18:36:08 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/miniRT.h"
#include "inc/miniRT_struct.h"
#include "minilibx_opengl/mlx.h"

t_img		*ft_new_img(t_mlx mlx, t_data *data)
{
	t_img	*img;

	if (!(img = malloc(sizeof(t_img))))
		return (NULL);
	img->image = mlx_new_image(mlx.mlx_ptr, data->render[0], data->render[1]);
	if (img->image == NULL)
		return (NULL);
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->stride, &img->endian);
	img->bpp = 1;
	return (img);
}

void	put_pixel_to_img(int x, int y, int color, t_data *data)
{
	if (x < 0 || x >= data->render[0] || y < 0 || y >= data->render[1])
		return ;
	*(int *)(data->img->ptr + ((x + y * data->render[0]) * data->img->bpp)) = color;
}
