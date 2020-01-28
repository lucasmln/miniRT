/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 12:56:02 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/19 17:25:28 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void		ft_get_norm_cy(t_vect3 *n, t_ray ray)
{
	t_vect3	temp;

	*n = ft_vec_diff(ray.origine, g_data->cy->coord);
	temp = ft_vec_mult_scalar(*n, ft_dot_product(*n, g_data->cy->coord));
	*n = ft_vec_diff(ray.origine, ft_vec_add(temp, g_data->cy->coord));
	*n = ft_normal_vector(*n);
	if (ft_dot_product(*n, ray.dir) > 0)
		*n = ft_vec_mult_scalar(*n, -1);
}

double		ft_for_each_cy(t_ray ray, t_vect3 *p, t_vect3 *n)
{
	double	hit;
	double	min;
	int		pos;

	min = -1;
	ft_go_start_lst("cylinder");
	while (1)
	{
		hit = ft_intersection_ray_cy(ray, g_data->cy);
		if (hit > EPS)
			if (min == -1 || fmin(hit, min) == hit)
			{
				*p = ft_vec_add(ft_vec_mult_scalar(ray.dir, hit), ray.origine);
				ft_get_norm_cy(n, ray);
				min = hit;
				pos = g_data->cy->rank;
			}
		if (g_data->cy->rank == -1)
			break ;
		g_data->cy = g_data->cy->next;
	}
	if (min > 0)
		while (g_data->cy->rank != pos)
			g_data->cy = g_data->cy->next;
	return (ft_intersection_ray_cy(ray, g_data->cy));
}

double		ft_intersection_ray_cy_2(t_vect3 hty, t_vect3 abc,
																t_vect3 cardoc)
{
	hty.x = sqrt(hty.x);
	hty.y = (-abc.y - hty.x) / abc.x;
	hty.z = cardoc.z + (hty.y * cardoc.y);
	if (hty.z > 0 && hty.z < cardoc.x)
		return (hty.y);
	hty.y = (((hty.z < 0) ? 0 : cardoc.x) - cardoc.z) / cardoc.y;
	hty.y = ((fabs(abc.y + (abc.x * hty.y)) < hty.x) && hty.y > 0) ? hty.y : 0;
	if (hty.y != 0)
		return (hty.y);
	return (0);
}

double		ft_intersection_ray_cy(t_ray ray, t_cylinder *cy)
{
	t_vect3		ca;
	t_vect3		oc;
	t_vect3		abc;
	t_vect3		hty;
	t_vect3		cardoc;

	ca = ft_vec_diff(ft_vec_add(cy->coord, ft_vec_mult_scalar(cy->dir,
		cy->height)), cy->coord);
	oc = ft_vec_diff(ray.origine, cy->coord);
	cardoc.x = ft_dot_product(ca, ca);
	cardoc.y = ft_dot_product(ca, ray.dir);
	cardoc.z = ft_dot_product(ca, oc);
	abc.x = cardoc.x - (cardoc.y * cardoc.y);
	abc.y = cardoc.x * ft_dot_product(oc, ray.dir) - (cardoc.z * cardoc.y);
	abc.z = cardoc.x * ft_dot_product(oc, oc) - (cardoc.z * cardoc.z)
			- ((cy->diameter / 2) * (cy->diameter / 2) * cardoc.x);
	hty.x = (abc.y * abc.y) - (abc.x * abc.z);
	if (hty.x < EPS)
		return (0);
	return (ft_intersection_ray_cy_2(hty, abc, cardoc));
}
