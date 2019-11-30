/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:51:04 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/30 19:33:04 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

double		ft_intersection_ray_pl(t_ray ray, t_plane *pl,
			t_vect3 *p, t_vect3 *n)
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
	if (t < 0)
		return (0);
	*p = ft_vec_add(ray.origine, ft_vec_mult_scalar(ray.dir, t));
	*n = norm;
	return (t);
}
