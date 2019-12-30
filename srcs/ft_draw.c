/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:20:49 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/30 19:09:15 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void		ft_create_ray(int x, int y)
{
	g_data->ray.origine.x = g_data->cam->coord.x;
	g_data->ray.origine.y = g_data->cam->coord.y;
	g_data->ray.origine.z = g_data->cam->coord.z;
	g_data->ray.dir.x = x - g_data->render[0] / 2;
	g_data->ray.dir.y = y - g_data->render[1] / 2;
	g_data->ray.dir.z = -g_data->render[1] /
						(2 * tan((ft_to_radian(g_data->cam->fov) / 2)));
	g_data->ray.dir = ft_normal_vector(g_data->ray.dir);
}

int			ft_inter_light(t_vect3 *p, t_vect3 *n)
{
	t_ray		ray_light;
	double		inter;
	t_vect3		tmp_p;
	t_vect3		tmp_n;

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
	if ((g_data->sp->trans == 1 && ft_strncmp(g_data->obj, "sp", 2) == 0) ||
	(g_data->pl->trans == 1 && ft_strncmp(g_data->obj, "pl", 2) == 0) ||
	(g_data->tr->trans == 1 && ft_strncmp(g_data->obj, "tr", 2) == 0) ||
	(g_data->sq->trans == 1 && ft_strncmp(g_data->obj, "sq", 2) == 0) ||
	(g_data->cy->trans == 1 && ft_strncmp(g_data->obj, "cy", 2) == 0))
		return (0);
	return (1);
}

int			ft_check_mirroir(t_ray ray, int coord[2], int nb)
{
	t_vect3		tmp;
	t_vect3		aux_dir;

	if ((g_data->sp->trans == 1 && ft_strncmp(g_data->obj, "sp", 2) == 0) ||
	(g_data->pl->trans == 1 && ft_strncmp(g_data->obj, "pl", 2) == 0) ||
	(g_data->tr->trans == 1 && ft_strncmp(g_data->obj, "tr", 2) == 0) ||
	(g_data->sq->trans == 1 && ft_strncmp(g_data->obj, "sq", 2) == 0) ||
	(g_data->cy->trans == 1 && ft_strncmp(g_data->obj, "cy", 2) == 0))
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
	double		n1;
	double		n2;
	double		radical;
	t_vect3		n_trans;
	t_vect3		color;

	color.x = -1;
	if (g_data->sp->trans == 1 && ft_strncmp(g_data->obj, "sp", 2) == 0)
	{
		g_data->check_trans = g_data->sp->ratio_trans;
		color = g_data->sp->color;
	}
	if (g_data->pl->trans == 1 && ft_strncmp(g_data->obj, "pl", 2) == 0)
	{
		g_data->check_trans = g_data->pl->ratio_trans;
		color = g_data->pl->color;
	}
	if (g_data->sq->trans == 1 && ft_strncmp(g_data->obj, "sq", 2) == 0)
	{
		g_data->check_trans = g_data->sq->ratio_trans;
		color = g_data->sq->color;
	}
	if (g_data->tr->trans == 1 && ft_strncmp(g_data->obj, "tr", 2) == 0)
	{
		g_data->check_trans = g_data->tr->ratio_trans;
		color = g_data->tr->color;
	}
	if (g_data->cy->trans == 1 && ft_strncmp(g_data->obj, "cy", 2) == 0)
	{
		g_data->check_trans = g_data->cy->ratio_trans;
		color = g_data->cy->color;
	}
	if (g_data->check_trans)
	{
		n1 = 1;
		n2 = g_data->check_trans;
		n_trans = g_data->inter.n;
		if (ft_dot_product(ray.dir, g_data->inter.n) > 0)
		{
			n1 = g_data->check_trans;
			n2 = 1;
			n_trans = ft_vec_mult_scalar(g_data->inter.n, -1);
		}
		radical = 1 - ft_sqr(n1 / n2) * (1 - ft_sqr(ft_dot_product(n_trans, ray.dir)));
		if (radical > 0)
		{
			g_data->ray_trans.origine = ft_vec_diff(g_data->inter.p,
					ft_vec_mult_scalar(n_trans, EPS));
			tmp = ft_vec_mult_scalar(ft_vec_diff(ray.dir, ft_vec_mult_scalar(n_trans,
					ft_dot_product(ray.dir, n_trans))), (n1 / n2));
			aux_dir = ft_vec_mult_scalar(n_trans, sqrt(radical));
			g_data->ray_trans.dir = ft_vec_diff(tmp,aux_dir);
			return (color);
		}
	}
	return (color);
}

t_vect3		ft_raytrace(t_ray ray, int coord[], int nb)
{
	double	inter;
	t_vect3	tmp_pix;

	g_data->check_trans = 0;
	inter = ft_for_each_obj(ray, &g_data->inter.p, &g_data->inter.n);
	if (inter)
	{
		tmp_pix = ft_check_transparence(ray, coord, nb);
		if (nb >= 0 && ft_check_mirroir(ray, coord, nb))
			g_data->pix = ft_raytrace(g_data->ray_mir, coord, nb - 1);
		else if (nb >= 0 && tmp_pix.x != -1)
		{
			g_data->pix = ft_vec_add(ft_vec_mult_scalar(tmp_pix, 0.2), ft_raytrace(g_data->ray_trans, coord, nb - 1));
			if (g_data->pix.x > 255)
				g_data->pix.x = 255;
			if (g_data->pix.y > 255)
				g_data->pix.y = 255;
			if (g_data->pix.z > 255)
				g_data->pix.z = 255;
		}
		else
		{
			g_data->pix = ft_get_pixel_color(g_data->inter.p, g_data->inter.n);
			if (g_data->check_trans != 1 && ft_inter_light(&g_data->inter.p, &g_data->inter.n))
				ft_reset_values(&g_data->pix);
		}
	}
	else
		g_data->pix = ft_vec_mult_scalar(ft_vec_mult_scalar(g_data->ambience.color,
					g_data->ambience.ratio), 0.8);
	return (g_data->pix);
}

void		ft_draw(void)
{
	int		coord[2];

	coord[0] = 0;
	while (coord[0] < g_data->render[0])
	{
		coord[1] = 0;
		while (coord[1] < g_data->render[1])
		{
			g_data->check = 0;
			if (coord[0] == 946 && coord[1] == 460)
				g_data->check = 2;
			ft_reset_values(&g_data->pix);
			ft_create_ray(coord[0], coord[1]);
			g_data->pix = ft_raytrace(g_data->ray, coord, 5);
		/*	if (data->check == 2)
			{
				data->pix.x = 0;
				data->pix.y = 0;
				data->pix.z = 255;
			}*/
			ft_put_pixel_to_img(coord[0], coord[1], ft_set_color(g_data->pix));
			coord[1]++;
		}
		coord[0]++;
	}
}
