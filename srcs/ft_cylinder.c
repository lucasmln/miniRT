/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 12:56:02 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/17 20:07:46 by lmoulin          ###   ########.fr       */
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
}
