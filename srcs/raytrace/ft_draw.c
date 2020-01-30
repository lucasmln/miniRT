/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:20:49 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/30 12:48:44 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void		ft_create_ray(int x, int y)
{
	t_vect3		tmp;

	tmp.x = g_data->cam->dir.x * -1 + 1;
	tmp.y = g_data->cam->dir.y * -1 + 1;
	tmp.z = g_data->cam->dir.z > 0 ? 1 : -1;
	g_data->ray.origine.x = g_data->cam->coord.x;
	g_data->ray.origine.y = g_data->cam->coord.y;
	g_data->ray.origine.z = g_data->cam->coord.z;
	g_data->ray.dir.x = x - (g_data->render[0] / 2) * tmp.x;
	g_data->ray.dir.y = y - (g_data->render[1] / 2) * tmp.y;
	g_data->ray.dir.z = tmp.z * (-g_data->render[1] /
						(2 * tan((ft_to_radian(g_data->cam->fov) / 2))));
	g_data->ray.dir = ft_normal_vector(g_data->ray.dir);
}

int			ft_raytrace_2(t_ray ray, int coord[], int nb, t_vect3 *tmp_pix)
{
	*tmp_pix = ft_check_transparence(ray);
	if (nb >= 0 && ft_check_mirroir(ray))
	{
		g_data->pix = ft_raytrace(g_data->ray_mir, coord, nb - 1);
		return (1);
	}
	else if (nb >= 0 && tmp_pix->x != -1)
	{
		g_data->pix = ft_vec_add(ft_vec_mult_scalar(*tmp_pix, 0.2),
							ft_raytrace(g_data->ray_trans, coord, nb - 1));
		if (g_data->pix.x > 255)
			g_data->pix.x = 255;
		if (g_data->pix.y > 255)
			g_data->pix.y = 255;
		if (g_data->pix.z > 255)
			g_data->pix.z = 255;
		return (1);
	}
	return (0);
}

t_vect3		ft_raytrace(t_ray ray, int coord[], int nb)
{
	double	inter;
	t_vect3	tmp_pix;

	g_data->check_trans = 0;
	inter = ft_for_each_obj(ray, &g_data->inter.p, &g_data->inter.n);
	if (inter)
	{
		if (ft_raytrace_2(ray, coord, nb, &tmp_pix))
			;
		else
		{
			g_data->pix = ft_get_pixel_color(g_data->inter.p, g_data->inter.n);
			if (g_data->check_trans != 1 && ft_inter_light(&g_data->inter.p,
															&g_data->inter.n))
				g_data->pix = ft_vec_mult_scalar(g_data->pix, g_data->ambience.ratio / 2);
		}
	}
	else
	{
		g_data->pix = ft_vec_mult_scalar(ft_vec_mult_scalar(
						g_data->ambience.color, g_data->ambience.ratio), 0.6);
		ft_check_abs_value(&g_data->pix);
	}
	return (g_data->pix);
}

void		ft_draw(void)
{
	int		coord[2];

	coord[0] = 0;
	while (coord[0] < g_data->render[0])
	{
		coord[1] = 0;
		while (coord[1] < g_data->render[1])
		{
			g_data->check = 0;
			if (coord[0] == 700 && coord[1] == 470)
				g_data->check = 1;
			ft_reset_values(&g_data->pix);
			ft_create_ray(coord[0], coord[1]);
			g_data->pix = ft_raytrace(g_data->ray, coord, 5);
			ft_put_pixel_to_img(coord[0], coord[1], ft_set_color(g_data->pix));
			coord[1]++;
		}
		coord[0]++;
	}
}
