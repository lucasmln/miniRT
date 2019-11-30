/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 19:18:51 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/30 20:08:35 by lmoulin          ###   ########.fr       */
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

t_vect3		ft_reset_vect(t_vect3 v)
{
	v.x = 0;
	v.y = 0;
	v.z = 0;
	return (v);
}

t_vect3		ft_get_pixel_color(t_data *data, t_vect3 p, t_vect3 n)
{
	double		intensite;
	t_vect3		max_pixel;
	int			check;

//	check = -1;
//	while (check)
//	{
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
//		if (check == -1 || ft_pix_cmp(max_pixel, data->pix) == 1)
//		{
//			check = 1;
//			max_pixel = data->pix;
//		}
//		if (data->light->rank == -1)
//			check = 0;
//		data->light = data->light->next;
//	}
	return (data->pix);
}
