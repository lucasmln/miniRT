/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:20:20 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/28 21:36:10 by lmoulin          ###   ########.fr       */
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

void		ft_reset_values(t_vect3 *pix)
{
	pix->x = 0;
	pix->y = 0;
	pix->z = 0;
}

int			ft_set_ambience_intensity(t_vect3 *ambiente, t_vect3 *intense)
{
	ambiente->x = (data->ambience.color.x / 255) * data->ambience.ratio;
	ambiente->y = (data->ambience.color.y / 255) * data->ambience.ratio;
	ambiente->z = (data->ambience.color.z / 255) * data->ambience.ratio;
	intense->x = 100000000 * data->light->ratio * (data->light->color.x / 255);
	intense->y = 100000000 * data->light->ratio * (data->light->color.y / 255);
	intense->z = 100000000 * data->light->ratio * (data->light->color.z / 255);
	return (1);
}

t_vect3		ft_get_pixel_color(t_data *data, t_vect3 p, t_vect3 n)
{
	t_vect3		param[3];

	ft_go_start_lst(data, "light");
	ft_reset_values(&param[2]);
	while (ft_set_ambience_intensity(&param[1], &param[0]))
	{
		if (data->color.x)
			param[2].x = (data->color.x / 255) * (param[0].x *
			ft_dot_product(ft_normal_vector(ft_vec_diff(data->light->coord, p)),
			n) * param[1].x / ft_get_norm2(ft_vec_diff(data->light->coord, p)));
		if (data->color.y)
			param[2].y = (data->color.y / 255) * (param[0].y *
			ft_dot_product(ft_normal_vector(ft_vec_diff(data->light->coord, p)),
			n) * param[1].y / ft_get_norm2(ft_vec_diff(data->light->coord, p)));
		if (data->color.z)
			param[2].z = (data->color.z / 255) * (param[0].z *
			ft_dot_product(ft_normal_vector(ft_vec_diff(data->light->coord, p)),
			n) * param[1].z / ft_get_norm2(ft_vec_diff(data->light->coord, p)));
		ft_check_abs_value(&param[2]);
		ft_pix_cmp(&param[2], &data->pix);
		if (data->light->rank == -1 || !(data->light = data->light->next))
			break ;
	}
	ft_go_start_lst(data, "light");
	return (data->pix);
}
