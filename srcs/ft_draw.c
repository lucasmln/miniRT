/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:20:49 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/16 15:36:37 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

double		ft_for_each_obj(t_ray ray, t_data *data, t_vect3 *p, t_vect3 *n)
{
	double	res;
	double	tmp;
	t_vect3	tmp_p;
	t_vect3	tmp_n;

	if (data->sp->next)
		res = ft_for_each_sp(ray, data, p, n);
	data->color = data->sp->color;
	if (data->pl->next)
		tmp = ft_for_each_pl(ray, data, &tmp_p, &tmp_n);
	if ((tmp > 0 && tmp < res && res > 0) || (res <= 0 && tmp > 0))
	{
		res = tmp;
		*p = tmp_p;
		*n = tmp_n;
		data->color = data->pl->color;
	}
	if (data->tr->next)
		tmp = ft_for_each_tr(ray, data, &tmp_p, &tmp_n);
	if ((tmp > 0 && tmp < res && res > 0) || (res <= 0 && tmp > 0))
	{
		res = tmp;
		*p = tmp_p;
		*n = tmp_n;
		data->color = data->tr->color;
	}
	return (res);
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
			break;
		data->light = data->light->next;
	}
	ft_go_start_lst(data, "light");
	return (1);
}

void		ft_raytrace(t_data *data, int x, int y)
{
	int	inter;
	t_vect3 p;
	t_vect3 n;

	data->check = 0;
	if (x == 100 && y == 550)
		data->check = 1;
	ft_create_ray(data, x, y);
	inter = ft_for_each_obj(data->ray, data, &p, &n);
	if (inter > 0)
	{
		data->pix = ft_get_pixel_color(data, p, n);
		if (ft_inter_light(data, &p, &n))
			ft_reset_values(&data->pix);
		ft_put_pixel_to_img(x, y, ft_set_color(data->pix), data);
	}
	else
	{
		data->pix.x = data->ambience.color.x * data->ambience.ratio * 0.8;
		data->pix.y = data->ambience.color.y * data->ambience.ratio * 0.8;
		data->pix.z = data->ambience.color.z * data->ambience.ratio * 0.8;
		ft_put_pixel_to_img(x, y, ft_set_color(data->pix), data);
		ft_put_pixel_to_img(x, y, 0, data);
	}
}

void		ft_draw(t_data *data)
{
	int		x;
	int		y;

	x = 0;
	while (x < data->render[0])
	{
		y = 0;
		while (y < data->render[1])
		{
			ft_reset_values(&data->pix);
			ft_raytrace(data, x, y);
			y++;
		}
		x++;
	}
}
