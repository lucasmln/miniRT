/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:20:49 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/25 15:59:42 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minirt.h"

void		ft_check_abs_value(t_vect3 *pixel)
{
	if (pixel->x > 255 || pixel->y > 255 || pixel->z > 255)
	{
		pixel->x = pixel->x > 255 ? 255 : pixel->x;
		pixel->y = pixel->y > 255 ? 255 : pixel->y;
		pixel->z = pixel->z > 255 ? 255 : pixel->z;
	}
	else if (pixel->x < 0 || pixel->y < 0 || pixel->z < 0)
	{
		pixel->x = pixel->x < 0 ? 0 : pixel->x;
		pixel->y = pixel->y < 0 ? 0 : pixel->y;
		pixel->z = pixel->z < 0 ? 0 : pixel->z;
	}
}

t_vect3		ft_get_pixel_color(t_data *data, t_vect3 p, t_vect3 n)
{
	double	intensite;

	intensite = 1000000 * 0.6;
	if (data->sp->color.x)
		data->pix.x = (data->sp->color.x / 255) * (intensite *
		ft_dot_product(ft_normal_vector(ft_vec_diff(data->light->coord, p)), n) /
		ft_get_norm2(ft_vec_diff(data->light->coord, p)));
	if (data->sp->color.y)
		data->pix.y = (data->sp->color.y / 255)* (intensite *
		ft_dot_product(ft_normal_vector(ft_vec_diff(data->light->coord, p)), n) /
		ft_get_norm2(ft_vec_diff(data->light->coord, p)));
	if (data->sp->color.z)
		data->pix.z = (data->sp->color.z / 255)* (intensite *
		ft_dot_product(ft_normal_vector(ft_vec_diff(data->light->coord, p)), n) /
		ft_get_norm2(ft_vec_diff(data->light->coord, p)));
	ft_check_abs_value(&data->pix);
	return (data->pix);
}

void		ft_create_ray(t_data *data, int i, int j)
{
	data->ray.origine.x = data->cam->coord.x;
	data->ray.origine.y = data->cam->coord.y;
	data->ray.origine.z = data->cam->coord.z;
	data->ray.dir.y = j - data->render[1] / 2;
	data->ray.dir.x = i - data->render[0] / 2;
	data->ray.dir.z = -data->render[1] /
						(2 * tan((ft_to_radian(data->cam->fov) / 2)));
	data->ray.dir = ft_normal_vector(data->ray.dir);
}

void		ft_draw(t_data *data)
{
	int x;
	int y;
	double valid_pixel;
	t_vect3 p;
	t_vect3 n;

	x = 0;
	while (x < data->render[0])
	{
		y = 0;
		while (y < data->render[1])
		{
			ft_create_ray(data, x, y);
			valid_pixel = ft_pixel_ray_sp(data->ray, data->sp, &p, &n);
			if (valid_pixel)
			{
				data->pix = ft_get_pixel_color(data, p, n);
				ft_put_pixel_to_img(x, y, ft_set_color(data->pix), data);
			}
			else
				ft_put_pixel_to_img(x, y, 0, data);
			y++;
		}
		x++;
	}
}
