/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:51:04 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/26 20:33:35 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
# define T_MIN 0.0001f
# define T_MAX 100000.0f

double		ft_pixel_ray_pl(t_ray r, t_plane *pl)
{
	double	t;
	double	ddotv;
	double	xdotv;
	t_vect3	x;

	x = ft_vec_diff(r.origine, pl->coord);
	ddotv = ft_dot_product(r.dir, pl->dir);
	xdotv = ft_dot_product(x, pl->dir);
	if (ddotv != 0)
	{
		t = -xdotv / ddotv;
		if (t > T_MIN && t < T_MAX)
			return (t);
	}
	return (T_MAX);
}

