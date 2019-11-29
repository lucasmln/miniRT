/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 12:56:02 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/29 14:52:39 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int		ft_intersection_ray_cy(t_ray ray, t_cylinder *cy, t_vect3 *p, t_vect3 *n)
{
	double	a;
	double	b;
	double	c;
	double	d;
	t_vect3	x;
	double m;

	x = ft_vec_diff(ray.origine, cy->coord);
	a = ft_dot_product(ray.dir, ray.dir) - pow(ft_dot_product(ray.dir, cy->dir), 2);
	b = 2 * (ft_dot_product(ray.dir, x) - (ft_dot_product(ray.dir, cy->dir) * ft_dot_product(x, cy->dir)));
	c = ft_dot_product(x, x) - pow(ft_dot_product(x, cy->dir), 2);
	d = (b * b) - (4 * a * c);
	if (d < 0)
		return (0);
	m = (-b - sqrt(d)) / (2.0f * a);
	*p = ft_vec_add(ray.origine, ft_vec_mult_scalar(ray.dir, d));
	*n = ft_normal_vector(ft_vec_diff(ft_vec_diff(*p, cy->coord), ft_vec_mult_scalar(cy->dir, m)));
	if (ft_dot_product(ray.dir, *n) > 0)
		*n = ft_vec_mult_scalar(*n, -1);
	return (1);
}
