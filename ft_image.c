/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:44:36 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/22 17:36:55 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minirt.h"
#include "minilibx_opengl/mlx.h"

void	ft_new_img(t_mlx mlx, t_data *data)
{
	t_img	*img;

	if (!(img = malloc(sizeof(t_img))))
		return ;
	img->image = mlx_new_image(mlx.mlx_ptr, data->render[0], data->render[1]);
	if (img->image == NULL)
		return ;
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->stride, &img->endian);
	img->bpp /= 8;
	data->img = img;
}

void	put_pixel_to_img(int x, int y, long color, t_data *data)
{
	if (x < 0 || x >= data->render[0] || y < 0 || y >= data->render[1])
		return ;
	printf("%lx = color\n", color);
	*(int *)(data->img->ptr + ((x + y * data->render[0]) * data->img->bpp)) = color;
}
