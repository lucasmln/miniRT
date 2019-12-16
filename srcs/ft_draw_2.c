/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:34:21 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/16 17:14:39 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void		ft_check_abs_value(t_vect3 *pixel)
{
	pixel->x = pow(pixel->x, 1 / 2.2);
	pixel->y = pow(pixel->y, 1 / 2.2);
	pixel->z = pow(pixel->z, 1 / 2.2);
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

void		ft_pix_cmp(t_vect3 *max_pix, t_vect3 *pix)
{
	if (max_pix->x > pix->x)
		pix->x = max_pix->x;
	if (max_pix->y > pix->y)
		pix->y = max_pix->y;
	if (max_pix->z > pix->z)
		pix->z = max_pix->z;
}

void	ft_reset_values(t_vect3 *pix)
{
	pix->x = 0;
	pix->y = 0;
	pix->z = 0;
}

t_vect3		ft_get_pixel_color(t_data *data, t_vect3 p, t_vect3 n)
{
	t_vect3		intensite;
	t_vect3		max_pixel;
	t_vect3		ambiente;
	int			check;

	while (data->light->rank != -1)
		data->light = data->light->next;
	data->light = data->light->next;
	check = -1;
	ft_reset_values(&max_pixel);
	while (check)
	{
		ambiente.x = (data->ambience.color.x / 255) * data->ambience.ratio;
		ambiente.y = (data->ambience.color.y / 255) * data->ambience.ratio;
		ambiente.z = (data->ambience.color.z / 255) * data->ambience.ratio;
		intensite.x = 100000000 * data->light->ratio * (data->light->color.x / 255);
		intensite.y = 100000000 * data->light->ratio * (data->light->color.y / 255);
		intensite.z = 100000000 * data->light->ratio * (data->light->color.z / 255);
		if (data->color.x)
			max_pixel.x = (data->color.x / 255) * (intensite.x *
			ft_dot_product(ft_normal_vector(ft_vec_diff(data->light->coord, p)), n)
			* ambiente.x / ft_get_norm2(ft_vec_diff(data->light->coord, p)));
		if (data->color.y)
			max_pixel.y = (data->color.y / 255) * (intensite.y *
			ft_dot_product(ft_normal_vector(ft_vec_diff(data->light->coord, p)), n)
			*ambiente.y / ft_get_norm2(ft_vec_diff(data->light->coord, p)));
		if (data->color.z)
			max_pixel.z = (data->color.z / 255) * (intensite.z *
			ft_dot_product(ft_normal_vector(ft_vec_diff(data->light->coord, p)), n)
			* ambiente.z / ft_get_norm2(ft_vec_diff(data->light->coord, p)));
		ft_check_abs_value(&max_pixel);
		ft_pix_cmp(&max_pixel, &data->pix);
		if (data->check == 2)
		{
			data->pix.x = 255;
			printf("r= %lf, g = %lf, b = %lf\n", data->pix.x, data->pix.y, data->pix.z);
		}
		if (data->light->rank == -1)
			check = 0;
		data->light = data->light->next;
	}
	while (data->light->rank != -1)
		data->light = data->light->next;
	data->light = data->light->next;
	return (data->pix);
}
