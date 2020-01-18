/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_effect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 20:34:17 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/18 21:04:29 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int			ft_check_obj_trans(void)
{
	if ((g_data->sp->trans == 1 && ft_strncmp(g_data->obj, "sp", 2) == 0) ||
	(g_data->pl->trans == 1 && ft_strncmp(g_data->obj, "pl", 2) == 0) ||
	(g_data->tr->trans == 1 && ft_strncmp(g_data->obj, "tr", 2) == 0) ||
	(g_data->sq->trans == 1 && ft_strncmp(g_data->obj, "sq", 2) == 0) ||
	(g_data->cy->trans == 1 && ft_strncmp(g_data->obj, "cy", 2) == 0))
		return (0);
	return (1);
}

void		ft_get_filter_color(t_vect3 *color)
{
	if (g_data->sp->trans == 1 && ft_strncmp(g_data->obj, "sp", 2) == 0)
	{
		g_data->check_trans = g_data->sp->ratio_trans;
		*color = g_data->sp->color;
	}
	if (g_data->pl->trans == 1 && ft_strncmp(g_data->obj, "pl", 2) == 0)
	{
		g_data->check_trans = g_data->pl->ratio_trans;
		*color = g_data->pl->color;
	}
	if (g_data->sq->trans == 1 && ft_strncmp(g_data->obj, "sq", 2) == 0)
	{
		g_data->check_trans = g_data->sq->ratio_trans;
		*color = g_data->sq->color;
	}
	if (g_data->tr->trans == 1 && ft_strncmp(g_data->obj, "tr", 2) == 0)
	{
		g_data->check_trans = g_data->tr->ratio_trans;
		*color = g_data->tr->color;
	}
	if (g_data->cy->trans == 1 && ft_strncmp(g_data->obj, "cy", 2) == 0)
	{
		g_data->check_trans = g_data->cy->ratio_trans;
		*color = g_data->cy->color;
	}
}

void		ft_set_indice_milieu_trans(t_ray *ray, double n[3],
															t_vect3 *n_trans)
{
	n[0] = 1;
	n[1] = g_data->check_trans;
	*n_trans = g_data->inter.n;
	if (ft_dot_product(ray->dir, g_data->inter.n) > 0)
	{
		n[0] = g_data->check_trans;
		n[1] = 1;
		*n_trans = ft_vec_mult_scalar(g_data->inter.n, -1);
	}
	n[2] = 1 - ft_sqr(n[0] / n[1]) * (1 - ft_sqr(ft_dot_product(*n_trans,
																	ray->dir)));
}

int			ft_check_mirroir(t_ray ray, int coord[2], int nb)
{
	t_vect3		tmp;
	t_vect3		aux_dir;

	if (ft_check_obj_trans() == 0)
		return (0);
	if ((g_data->sp->spec == 1 && ft_strncmp(g_data->obj, "sp", 2) == 0) ||
		(g_data->pl->spec == 1 && ft_strncmp(g_data->obj, "pl", 2) == 0) ||
		(g_data->tr->spec == 1 && ft_strncmp(g_data->obj, "tr", 2) == 0) ||
		(g_data->sq->spec == 1 && ft_strncmp(g_data->obj, "sq", 2) == 0) ||
		(g_data->cy->spec == 1 && ft_strncmp(g_data->obj, "cy", 2) == 0))
	{
		g_data->ray_mir.origine = ft_vec_add(g_data->inter.p,
					ft_vec_mult_scalar(g_data->inter.n, EPS));
		tmp = ft_vec_mult_scalar(g_data->inter.n,
				ft_dot_product(g_data->inter.n, ray.dir));
		aux_dir = ft_vec_diff(ray.dir, ft_vec_mult_scalar(tmp, 2));
		g_data->ray_mir.dir = aux_dir;
		return (1);
	}
	return (0);
}

t_vect3		ft_check_transparence(t_ray ray, int coord[2], int nb)
{
	t_vect3		tmp;
	t_vect3		aux_dir;
	double		n[3];
	t_vect3		n_trans;
	t_vect3		color;

	color.x = -1;
	ft_get_filter_color(&color);
	if (g_data->check_trans)
	{
		ft_set_indice_milieu_trans(&ray, n, &n_trans);
		if (n[2] > 0)
		{
			g_data->ray_trans.origine = ft_vec_diff(g_data->inter.p,
					ft_vec_mult_scalar(n_trans, EPS));
			tmp = ft_vec_mult_scalar(ft_vec_diff(ray.dir, ft_vec_mult_scalar(
					n_trans, ft_dot_product(ray.dir, n_trans))), (n[0] / n[1]));
			aux_dir = ft_vec_mult_scalar(n_trans, sqrt(n[2]));
			g_data->ray_trans.dir = ft_vec_diff(tmp, aux_dir);
			return (color);
		}
	}
	return (color);
}

int			ft_inter_light(t_vect3 *p, t_vect3 *n)
{
	t_ray		ray_light;
	double		inter;
	t_vect3		tmp_p;
	t_vect3		tmp_n;

	if (g_data->light->rank == 0)
		return (0);
	ft_go_start_lst("light");
	while (1)
	{
		ray_light.origine = ft_vec_add(*p, ft_vec_mult_scalar(*n, EPS));
		ray_light.dir = ft_normal_vector(ft_vec_diff(g_data->light->coord, *p));
		inter = ft_for_each_obj(ray_light, &tmp_p, &tmp_n);
		if (inter < EPS || inter * inter >
				ft_get_norm2(ft_vec_diff(g_data->light->coord, *p)))
			return (0);
		if (g_data->light->rank == -1)
			break ;
		g_data->light = g_data->light->next;
	}
	ft_go_start_lst("light");
	return (ft_check_obj_trans());
}
