/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:20:49 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/30 20:10:54 by lmoulin          ###   ########.fr       */
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

double		ft_for_each_obj(t_ray ray, t_data *data, t_vect3 *p, t_vect3 *n)
{
	double	res;
	double	tmp;
	t_vect3	tmp_p;
	t_vect3	tmp_n;

	res = ft_for_each_sp(ray, data, p, n);
	data->color = data->sp->color;
	tmp = ft_intersection_ray_pl(data->ray, data->pl, &tmp_p, &tmp_n);
	if ((tmp > 0 && tmp <= res && res > 0) || (res <= 0 && tmp > 0))
	{
		res = tmp;
		*p = tmp_p;
		*n = tmp_n;
		data->color = data->pl->color;
	}
	return (res);
}

void		ft_raytrace(t_data *data, int x, int y)
{
	double		inter;
	t_vect3		n;
	t_vect3		p;

	ft_create_ray(data, x, y);
	inter = ft_for_each_obj(data->ray, data, &p, &n);
	if (inter > 0)
	{
		data->pix = ft_reset_vect(data->pix);
		printf("r = %lf,g = %lf, b = %lf\n", data->pix.x, data->pix.y, data->pix.z);
		data->pix = ft_get_pixel_color(data, n, p);
		ft_put_pixel_to_img(x, y, ft_set_color(data->pix), data);
		while (data->sp->rank != 1)
			data->sp = data->sp->next;
	}
	else
		ft_put_pixel_to_img(x, y, ft_set_color(data->ambience.color), data);
}

void		ft_draw(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->render[0])
	{
		y = 0;
		while (y < data->render[1])
		{
			ft_raytrace(data, x, y);
			y++;
		}
		x++;
	}
}
