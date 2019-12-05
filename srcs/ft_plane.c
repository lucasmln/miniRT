/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:51:04 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/03 15:20:07 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

double		ft_for_each_pl(t_ray ray, t_data *data, t_vect3 *p, t_vect3 *n)
{
	double	inter;
	double	min;
	int		check;
	int		pos;

	check = 1;
	pos = data->pl->rank;
	min = -1;
	while (data->pl->rank != -1)
		data->pl = data->pl->next;
	data->pl = data->pl->next;
	while (check)
	{
		inter = ft_intersection_ray_pl(ray, data->pl, p, n);
		if (inter != 0)
		{
			if (min == -1 || fmin(inter, min) == inter)
			{
				min = inter;
				pos = data->pl->rank;
			}
		}
		if (data->pl->rank == -1)
			check = 0;
		data->pl = data->pl->next;
	}
	if (min > 0)
		while (data->pl->rank != pos)
			data->pl = data->pl->next;
	return (ft_intersection_ray_pl(ray, data->pl, p, n));
}

double		ft_intersection_ray_pl(t_ray ray, t_plane *pl, t_vect3 *p, t_vect3 *n)
{
	double	t;
	double	a;
	double	b;
	t_vect3	x;
	t_vect3 norm;

	norm = ft_normal_vector(pl->dir);
	x = ft_vec_diff(ray.origine, pl->coord);
	a = ft_dot_product(x, norm);
	b = ft_dot_product(ray.dir, norm);
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return (0);
	t = -a / b;
	if (t < EPS)
		return (0);
	*p = ft_vec_add(ray.origine, ft_vec_mult_scalar(ray.dir, t));
	if (ft_dot_product(ray.dir, norm) < 0)
		*n = norm;
	else
		*n = ft_vec_mult_scalar(norm, -1);
	return (t);
}
