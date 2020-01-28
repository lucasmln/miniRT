/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:20:20 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/21 11:25:34 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

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

void		ft_reset_values(t_vect3 *pix)
{
	pix->x = 0;
	pix->y = 0;
	pix->z = 0;
}

int			ft_set_ambience_intensity(t_vect3 *ambiente, t_vect3 *intense)
{
	ambiente->x = (g_data->ambience.color.x / 255) * g_data->ambience.ratio;
	ambiente->y = (g_data->ambience.color.y / 255) * g_data->ambience.ratio;
	ambiente->z = (g_data->ambience.color.z / 255) * g_data->ambience.ratio;
	intense->x = 100000000 * g_data->light->ratio * (g_data->light->color.x /
																		255);
	intense->y = 100000000 * g_data->light->ratio * (g_data->light->color.y /
																		255);
	intense->z = 100000000 * g_data->light->ratio * (g_data->light->color.z /
																		255);
	if (ambiente->x < 0.001 && ambiente->y < 0.001 && ambiente->z < 0.001)
		*ambiente = ft_vect_add_scalar(*ambiente, 0.001);
	return (1);
}

void		ft_calc_color(t_vect3 *p, t_vect3 *n, t_vect3 param[3])
{
	if (g_data->color.x)
		param[2].x = (g_data->color.x / 255) * (param[0].x *
		ft_dot_product(ft_normal_vector(ft_vec_diff(g_data->light->coord, *p)),
		*n) * param[1].x / ft_get_norm2(ft_vec_diff(g_data->light->coord, *p)));
	if (g_data->color.y)
		param[2].y = (g_data->color.y / 255) * (param[0].y *
		ft_dot_product(ft_normal_vector(ft_vec_diff(g_data->light->coord, *p)),
		*n) * param[1].y / ft_get_norm2(ft_vec_diff(g_data->light->coord, *p)));
	if (g_data->color.z)
		param[2].z = (g_data->color.z / 255) * (param[0].z *
		ft_dot_product(ft_normal_vector(ft_vec_diff(g_data->light->coord, *p)),
		*n) * param[1].z / ft_get_norm2(ft_vec_diff(g_data->light->coord, *p)));
}

t_vect3		ft_get_pixel_color(t_vect3 p, t_vect3 n)
{
	t_vect3		param[3];

	if (g_data->light->rank == 0)
	{
		g_data->light->color = g_data->ambience.color;
		g_data->light->ratio = g_data->ambience.ratio;
	}
	ft_go_start_lst("light");
	ft_reset_values(&param[2]);
	while (ft_set_ambience_intensity(&param[1], &param[0]))
	{
		if (g_data->light->rank == 0)
			param[2] = ft_vec_mult_scalar(g_data->color, g_data->ambience.ratio
																		* 10);
		else
			ft_calc_color(&p, &n, param);
		ft_check_abs_value(&param[2]);
		ft_pix_cmp(&param[2], &g_data->pix);
		if (g_data->light->rank == 0 || g_data->light->rank == -1 ||
										!(g_data->light = g_data->light->next))
			break ;
	}
	ft_go_start_lst("light");
	return (g_data->pix);
}
