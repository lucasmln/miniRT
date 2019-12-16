/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:59:28 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/16 17:06:04 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

double		ft_for_each_tr(t_ray ray, t_data *data, t_vect3 *p, t_vect3 *n)
{
	double	inter;
	double	min;
	int		check;
	int		pos;

	check = 1;
	pos = data->tr->rank;
	min = -1;
	while (data->tr->rank != -1)
		data->tr = data->tr->next;
	data->tr = data->tr->next;
	while (check)
	{
		inter = ft_intersection_ray_tr(ray, data->tr, p, n);
		if (inter != 0)
		{
			if (min == -1 || fmin(inter, min) == inter)
			{
				min = inter;
				pos = data->tr->rank;
			}
		}
		if (data->tr->rank == -1)
			check = 0;
		data->tr = data->tr->next;
	}
	if (min > 0)
		while (data->tr->rank != pos)
			data->tr = data->tr->next;
	return (ft_intersection_ray_tr(ray, data->tr, p, n));
}

double		ft_intersection_ray_tr(t_ray ray, t_triangle *tr,
								t_vect3 *p, t_vect3 *n)
{
	t_vect3	pvec;
	t_vect3	tvec;
	t_vect3	qvec;
	t_vect3	e1;
	t_vect3	e2;
	t_vect3	norm;
	t_vect3 center;
	double	det;
	double	inv;
	double	u;
	double	v;
	double	t;

	e1 = ft_vec_diff(tr->p_2, tr->p_1);
	e2 = ft_vec_diff(tr->p_3, tr->p_1);
	pvec = ft_cross_product(ray.dir, e2);
	det = ft_dot_product(e1, pvec);
	if (det < EPS)
		return (0);
	inv = 1.0 / det;
	tvec = ft_vec_diff(ray.origine, tr->p_1);
	u = ft_dot_product(tvec, pvec) * inv;
	if (u < 0.0 || u > 1.0)
		return (0);
	qvec = ft_cross_product(tvec, e1);
	v = ft_dot_product(ray.dir, qvec) * inv;
	if (v < 0.0 || u + v > 1.0)
		return (0);
	t = ft_dot_product(e2, qvec) * inv;
	*p = ft_vec_add(ray.origine, ft_vec_mult_scalar(ray.origine, t));
	norm = ft_normal_vector(ft_cross_product(e1, e2));
	*n = ft_normal_vector(norm);
	if (ft_dot_product(ray.dir, norm) > 0)
		*n = norm;
	else
		*n = ft_vec_mult_scalar(norm, -1);
	return (t);
}
