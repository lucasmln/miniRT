/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:05:22 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/25 15:10:51 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minirt.h"

int		ft_pixel_ray_sp(t_ray ray, t_sphere *sp, t_vect3 *v, t_vect3 *n)
{
	double	norm_2;
	t_vect3	var;
	double	sol[2];
	double	delta;
	double	res;

	var.x = 1;
	var.y = 2 * ft_dot_product(ray.dir, ft_vec_diff(ray.origine, sp->coord));
	norm_2 = ft_get_norm2(ft_vec_diff(ray.origine, sp->coord));
	var.z = norm_2 - (sp->diameter / 2) * (sp->diameter / 2);
	delta = var.y * var.y - 4 * var.x * var.z;
	if (delta < 0)
		return (0);
	sol[0] = (-var.y - sqrt(delta)) / (2 * var.x);
	sol[1] = (-var.y + sqrt(delta)) / (2 * var.x);
	if (sol[1] < 0)
		return (0);
	if (sol[0] > 0)
		res = sol[0];
	else
		res = sol[1];
	*v = ft_vec_add(ray.origine, ft_vec_mult_scalar(ray.dir, res));
	*n = ft_normal_vector(ft_vec_diff(*v, sp->coord));
	return (1);
}