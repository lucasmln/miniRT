/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:20:49 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/29 17:46:09 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

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

int		ft_pix_cmp(t_vect3 pix1, t_vect3 pix2)
{
	if (pix1.x <= pix2.x)
		if (pix1.y <= pix2.y)
			if (pix1.z <= pix2.z)
				return (1);
	return (0);
}

t_vect3		ft_get_pixel_color(t_data *data, t_vect3 p, t_vect3 n)
{
	double		intensite;
	t_vect3		max_pixel;
	int			check;

	check = -1;
	while (check)
	{
		intensite = 1000000 * data->light->ratio;
		if (data->sp->color.x)
			data->pix.x = (data->sp->color.x / 255) * (intensite *
			ft_dot_product(ft_normal_vector(ft_vec_diff(data->light->coord, p)), n) /
			ft_get_norm2(ft_vec_diff(data->light->coord, p)));
		if (data->sp->color.y)
			data->pix.y = (data->sp->color.y / 255) * (intensite *
			ft_dot_product(ft_normal_vector(ft_vec_diff(data->light->coord, p)), n) /
			ft_get_norm2(ft_vec_diff(data->light->coord, p)));
		if (data->sp->color.z)
			data->pix.z = (data->sp->color.z / 255) * (intensite *
			ft_dot_product(ft_normal_vector(ft_vec_diff(data->light->coord, p)), n) /
			ft_get_norm2(ft_vec_diff(data->light->coord, p)));
		ft_check_abs_value(&data->pix);
		if (check == -1 || ft_pix_cmp(max_pixel, data->pix) == 1)
		{
			check = 1;
			printf("rank = %d\n", data->light->rank);
			max_pixel.x = data->pix.x;
			max_pixel.y = data->pix.y;
			max_pixel.z = data->pix.z;
		}
		if (data->light->rank == -1)
			check = 0;
		data->light = data->light->next;
	}
	return (max_pixel);
}

void		ft_create_ray(t_data *data, int x, int y)
{
	data->ray.origine.x = data->cam->coord.x;
	data->ray.origine.y = data->cam->coord.y;
	data->ray.origine.z = data->cam->coord.z;
	data->ray.dir.x = x - data->render[0] / 2;
	data->ray.dir.y = y - data->render[1] / 2;
	data->ray.dir.z = -data->render[1] /
						(2 * tan((ft_to_radian(data->cam->fov) / 2)));
	data->ray.dir = ft_normal_vector(data->ray.dir);
}

void		ft_draw(t_data *data)
{
	int x;
	int y;
	int valid_pixel;
	t_vect3 p;
	t_vect3 n;

	x = 0;
	while (x < data->render[0])
	{
		y = 0;
		while (y < data->render[1])
		{
			ft_create_ray(data, x, y);
//			valid_pixel = ft_intersection_ray_cy(data->ray, data->cy, &n, &p);
			valid_pixel = ft_for_each_sp(data->ray, data->sp, &p, &n);
			if (valid_pixel)
			{
				while (data->sp->rank != valid_pixel)
					data->sp = data->sp->next;
		//		while (data->light->rank != 1)
		//			data->light = data->light->next;
				data->pix = ft_get_pixel_color(data, p, n);
				ft_put_pixel_to_img(x, y, ft_set_color(data->pix), data);
				while (data->sp->rank != 1)
					data->sp = data->sp->next;
			}
			else
				ft_put_pixel_to_img(x, y, 0, data);
			y++;
		}
		x++;
	}
}
