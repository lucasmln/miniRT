/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:51:04 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/27 12:51:47 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

double		ft_pixel_ray_pl(t_ray r, t_plane *pl)
{
	double	a;
	double	b;
	t_vect3	d;
	t_vect3	norm;
	double	angle;
	double res;
/*
	norm = ft_normal_vector(pl->coord);
	d = ft_vect_multiplication(pl->dir, norm);
	res = ft_ft_vect_diff(d, ft_vect_multiplication(r.origine, norm))), (ft_vect_multiplication(r.dir, norm));
	angle = acos((pow(c, 2) - pow(a, 2) - pow(b, 2)) / (2 * a * b));
*/	return (1);
}

