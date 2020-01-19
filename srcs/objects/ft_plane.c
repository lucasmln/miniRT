/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:51:04 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/19 14:40:56 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

double		ft_for_each_pl(t_ray ray, t_vect3 *p, t_vect3 *n)
{
	double	inter;
	double	min;
	int		pos;

	pos = g_data->pl->rank;
	min = -1;
	ft_go_start_lst("plane");
	while (1)
	{
		inter = ft_intersection_ray_pl(ray, g_data->pl, p, n);
		if (inter != 0)
			if (min == -1 || fmin(inter, min) == inter)
			{
				min = inter;
				pos = g_data->pl->rank;
			}
		if (g_data->pl->rank == -1)
			break ;
		g_data->pl = g_data->pl->next;
	}
	if (min > 0)
		while (g_data->pl->rank != pos)
			g_data->pl = g_data->pl->next;
	return (ft_intersection_ray_pl(ray, g_data->pl, p, n));
}

double		ft_intersection_ray_pl(t_ray ray, t_plane *pl, t_vect3 *p,
					t_vect3 *n)
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
