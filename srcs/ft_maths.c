/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:16:29 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/20 15:30:30 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

double		ft_to_radian(double degre)
{
	return (degre * M_PI / 180.0);
}

t_vect3		ft_vec_sub(t_vect3 a, t_vect3 b)
{
	t_vect3		v1;
	t_vect3		v2;

	v1 = a;
	v2 = ft_vec_mult_scalar(b, -1);
	return (ft_vec_add(v1, v2));
}

double		ft_distance(t_vect3 v1, t_vect3 v2)
{
	return (sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) +
			pow(v1.z - v2.z, 2)));
}

double		ft_sqr(double a)
{
	return (a * a);
}
