/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calcul_vect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:42:05 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/21 11:21:29 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vect3		ft_vec_div_scalar(t_vect3 v1, double d)
{
	t_vect3 res;

	res.x = v1.x / d;
	res.y = v1.y / d;
	res.z = v1.z / d;
	return (res);
}

double		ft_get_norm2(t_vect3 v1)
{
	return (v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
}

t_vect3		ft_normal_vector(t_vect3 v)
{
	t_vect3 res;
	double	norm;

	norm = sqrt(ft_get_norm2(v));
	res.x = v.x / norm;
	res.y = v.y / norm;
	res.z = v.z / norm;
	return (res);
}

t_vect3		ft_vect_multiplication(t_vect3 v1, t_vect3 v2)
{
	t_vect3 res;

	res.x = v1.x * v2.x;
	res.y = v1.y * v2.y;
	res.z = v1.z * v2.z;
	return (res);
}

t_vect3		ft_vect_add_scalar(t_vect3 v, double d)
{
	v.x += d;
	v.y += d;
	v.z += d;
	return (v);
}
