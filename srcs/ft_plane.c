/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:51:04 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/27 17:03:48 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

double		ft_pixel_ray_pl(t_ray ray, t_plane *pl, t_vect3 *n, t_vect3 *p)
{
	double	res;

	res = ft_dot_product(ft_normal_vector(pl->coord), ray.dir);
	if (res <= 0)
		return (0);
	*p = ft_vec_diff(pl->coord, ray.origine);
	*n = ft_normal_vector(*p);
	printf("1\n");
	return (1);
}

