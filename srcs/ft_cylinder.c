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
	t_vect3		l;
	t_vect3		w1;
	double		k;
	double		a;
	t_vect3		v;
	t_vect3		D;
	double		d;

	l = ft_vec_diff(ray.origine, cy->dir);
	w1 = ft_cross_product(ray.dir, cy->dir);
	k = ft_dot_product(w1, w1);
	if (k * k == 0)
	{
		v = ft_vect_multiplication(cy->coord, cy->dir);
		a = ft_dot_product(l, v);
		D = ft_vec_diff(l, ft_vec_mult_scalar(v, a));
		d = ft_dot_product(D, D);
		if (d > cy->diameter / 2)
			return (0);
		
		return (1);
	}






/*	double	a;
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
*/	return (1);
}
