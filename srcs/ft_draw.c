/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:20:49 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/17 20:19:32 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

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

int			ft_inter_light(t_data *data, t_vect3 *p, t_vect3 *n)
{
	t_ray		ray_light;
	double		inter;
	t_vect3		tmp_p;
	t_vect3		tmp_n;

	ft_go_start_lst(data, "light");
	while (1)
	{
		ray_light.origine = ft_vec_add(*p, ft_vec_mult_scalar(*n, EPS));
		ray_light.dir = ft_normal_vector(ft_vec_diff(data->light->coord, *p));
		inter = ft_for_each_obj(ray_light, data, &tmp_p, &tmp_n);
		if (inter < EPS || inter * inter >
				ft_get_norm2(ft_vec_diff(data->light->coord, *p)))
			return (0);
		if (data->light->rank == -1)
			break ;
		data->light = data->light->next;
	}
	ft_go_start_lst(data, "light");
	return (1);
}

int			ft_check_mirroir(t_ray ray, t_data *data, int coord[2], int nb)
{
	t_vect3		tmp;
	t_vect3		aux_dir;

	if ((data->sp->spec == 1 && ft_strncmp(data->obj, "sp", 2) == 0) ||
		(data->pl->spec == 1 && ft_strncmp(data->obj, "pl", 2) == 0) ||
		(data->tr->spec == 1 && ft_strncmp(data->obj, "tr", 2) == 0))
	{
		data->ray_mir.origine = ft_vec_add(data->inter.p,
					ft_vec_mult_scalar(data->inter.n, EPS));
		tmp = ft_vec_mult_scalar(data->inter.n,
				ft_dot_product(data->inter.n, ray.dir));
		aux_dir = ft_vec_diff(ray.dir, ft_vec_mult_scalar(tmp, 2));
		data->ray_mir.dir = aux_dir;
		return (1);
	}
	else
		return (0);
}

t_vect3		ft_raytrace(t_ray ray, t_data *data, int coord[], int nb)
{
	double	inter;

	inter = ft_for_each_obj(ray, data, &data->inter.p, &data->inter.n);
	if (inter)
	{
		if (nb >= 0 && ft_check_mirroir(ray, data, coord, nb))
			data->pix = ft_raytrace(data->ray_mir, data, coord, nb - 1);
		else
		{
			data->pix = ft_get_pixel_color(data, data->inter.p, data->inter.n);
			if (ft_inter_light(data, &data->inter.p, &data->inter.n))
				ft_reset_values(&data->pix);
		}
	}
	else
		data->pix = ft_vec_mult_scalar(ft_vec_mult_scalar(data->ambience.color,
					data->ambience.ratio), 0.8);
	return (data->pix);
}

void		ft_draw(t_data *data)
{
	int		coord[2];

	coord[0] = 0;
	while (coord[0] < data->render[0])
	{
		coord[1] = 0;
		while (coord[1] < data->render[1])
		{
			data->check = 0;
			if (coord[0] == 22 && coord[1] == 888)
				data->check = 2;
			ft_reset_values(&data->pix);
			ft_create_ray(data, coord[0], coord[1]);
			data->pix = ft_raytrace(data->ray, data, coord, 5);
		/*	if (data->check == 2)
			{
				data->pix.x = 0;
				data->pix.y = 0;
				data->pix.z = 255;
			}*/
			ft_put_pixel_to_img(coord[0], coord[1], ft_set_color(data->pix), data);
			coord[1]++;
		}
		coord[0]++;
	}
}
