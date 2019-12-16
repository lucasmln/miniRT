/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 12:59:28 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/16 19:21:49 by lmoulin          ###   ########.fr       */
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

double		ft_intersection_ray_tr(t_ray ray, t_triangle *tr, t_vect3 *p, t_vect3 *n)
{
	double		t;

	t_vect3		u;
	t_vect3		v;
	t_vect3		w;
	double		m[4];
	double		b[4];
	double		g[4];
	double		alpha;

	*n = ft_normal_vector(ft_cross_product(ft_vec_diff(tr->p_2, tr->p_1), ft_vec_diff(tr->p_3, tr->p_1)));
	t = ft_dot_product(ft_vec_diff(tr->p_3, ray.origine), *n) / ft_dot_product(ray.dir, *n);
	if (t < 0)
		return (0);
	*p = ft_vec_add(ray.origine, ft_vec_mult_scalar(ray.dir, t));
	u = ft_vec_diff(tr->p_2, tr->p_1);
	v = ft_vec_diff(tr->p_3, tr->p_1);
	w = ft_vec_diff(*p, tr->p_1);
	m[0] = ft_get_norm2(u);
	m[1] = ft_dot_product(u, v);
	m[2] = ft_get_norm2(v);
	m[3] = m[0] * m[2] - m[1] * m[1];

	b[0] = ft_dot_product(w, u);
	b[1] = ft_dot_product(w, v);
	b[2] = b[0] * m[2] - b[1] * m[1];
	b[3] = b[2] / m[3];

	g[0] = b[0];
	g[1] = b[1];
	g[2] = m[0] * g[1] - m[1] * g[0];
	g[3] = g[2] / m[3];

	alpha = 1 - b[3] - g[3];
	if (alpha < 0 || alpha > 1 || b[3] < 0 || b[3] > 1 || g[3] < 0 || g[3] > 1)
		return (0);
	return (t);
}
