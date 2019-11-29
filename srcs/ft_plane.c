/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:51:04 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/29 14:34:47 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

double		ft_pixel_ray_pl(t_ray ray, t_plane *pl, t_vect3 *n, t_vect3 *p)
{
	double		r;
	t_vect3		norm;
	double		d;

	norm = ft_normal_vector(pl->dir);
	d = -ft_dot_product(norm, pl->coord);
	return (1);
}

