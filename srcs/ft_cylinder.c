/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 12:56:02 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/29 01:07:01 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_vect3		ft_get_norm_cylinder(t_cylinder *cy, t_vect3 *p)
{
	double		height;
	t_vect3		tmp;

	height = ft_dot_product(ft_vec_diff(*p, cy->coord), cy->dir);
	tmp = ft_vec_add(cy->coord, ft_vec_mult_scalar(cy->dir, height));
	tmp = ft_vec_diff(*p, tmp);
	return (tmp);
}

t_vect3		ft_get_norm_cylinder2(t_cylinder *cy, t_vect3 *p)
{
	double	radius;
	t_vect3	tmp_n;
	t_vect3	tmp_p;

	radius = cy->diameter / 2;
	if (p->y < cy->coord.x + radius && p->x > cy->coord.x - radius && p->z >
		cy->coord.z + radius && p->z > cy->coord.z - radius)
	{
		if (p->y < cy->coord.y + cy->height + EPS && p->y > cy->coord.y + cy->height - EPS)
		{
			tmp_n.x = 0;
			tmp_n.y = 1;
			tmp_n.z = 0;
		}
		if (p->y < cy->coord.y + EPS && p->y > cy->coord.y - EPS)
		{
			tmp_n.x = 0;
			tmp_n.y = -1;
			tmp_n.z = 0;
		}
	}
	tmp_p.x = cy->coord.x;
	tmp_p.y = p->y;
	tmp_p.z = cy->coord.z;
	tmp_n = ft_vec_diff(*p, tmp_p);
	tmp_n = ft_normal_vector(tmp_n);
	return (tmp_n);
}

double		ft_for_each_cy(t_ray ray, t_data *data, t_vect3 *p, t_vect3 *n)
{
	double	inter;
	double	min;
	int		pos;
	t_vect3	temp;

	pos = data->cy->rank;
	min = -1;
	ft_go_start_lst(data, "cylinder");
	while (1)
	{
		inter = ft_intersection_ray_cy(ray, data->cy, p, n);
		if (inter > 0)
			if (min == -1 || fmin(inter, min) == inter)
			{
	//			*p = ft_vec_add(ft_vec_mult_scalar(ray.dir, inter), ray.origine);
	//			*n = ft_normal_vector(ft_get_norm_cylinder(data->cy, p));
			//		*n = ft_get_norm_cylinder(data->cy, p);
				*n = ft_vec_diff(ray.origine, data->cy->coord);
				temp = ft_vec_mult_scalar(*n, ft_dot_product(*n, data->cy->coord));
				*n = ft_vec_diff(ray.origine, ft_vec_add(temp, data->cy->coord));
				*n = ft_normal_vector(*n);
				if (ft_dot_product(*n, ray.dir) > 0)
					*n = ft_vec_mult_scalar(*n, -1);
				if (data->check == 2)
				{
					printf("n.x = %lf, n.y = %lf, n.z = %lf, inter  = %lf\n", n->x, n->y, n->z, inter);
					printf("p.x = %lf, p.y = %lf, p.z = %lf, inter  = %lf\n", p->x, p->y, p->z, inter);
				}
				min = inter;
				pos = data->cy->rank;
			}
		if (data->cy->rank == -1)
			break ;
		data->cy= data->cy->next;
	}
	if (min > 0)
		while (data->cy->rank != pos)
			data->cy = data->cy->next;
	return (ft_intersection_ray_cy(ray, data->cy, p, n));
}

double		ft_intersection_ray_cy(t_ray ray, t_cylinder *cy, t_vect3 *p, t_vect3 *n)
{
	t_vect3		ca;
	t_vect3		oc;
	t_vect3		abc;
	t_vect3		hty;
	t_vect3		cardoc;
	t_vect3		cy_pb;

	cy_pb = ft_vec_add(cy->coord, ft_vec_mult_scalar(cy->dir, cy->height));
	ca = ft_vec_diff(cy_pb, cy->coord);
	oc = ft_vec_diff(ray.origine, cy->coord);
	cardoc.x = ft_dot_product(ca, ca);
	cardoc.y = ft_dot_product(ca, ray.dir);
	cardoc.z = ft_dot_product(ca, oc);
	abc.x = cardoc.x - (cardoc.y * cardoc.y);
	abc.y = cardoc.x * ft_dot_product(oc, ray.dir) - (cardoc.z * cardoc.y);
	abc.z = cardoc.x * ft_dot_product(oc, oc) - (cardoc.z * cardoc.z)
			- ((cy->diameter / 2) * (cy->diameter / 2) * cardoc.x);
	hty.x = (abc.y * abc.y) - (abc.x * abc.z);
	if (hty.x < EPS)
		return (0);
	hty.x = sqrt(hty.x);
	hty.y = (-abc.y - hty.x) / abc.x;
	hty.z = cardoc.z + (hty.y * cardoc.y);
	if (hty.z > 0 && hty.z < cardoc.x)
	{
		*p = ft_vec_add(ft_vec_mult_scalar(ray.dir, hty.y), ray.origine);
//		*n = ft_normal_vector(ft_get_norm_cylinder2(data->cy, p));
		return (hty.y);
	}
	hty.y = (((hty.z < 0) ? 0 : cardoc.x) - cardoc.z) / cardoc.y;
	hty.y = ((fabs(abc.y + (abc.x * hty.y)) < hty.x) && hty.y > 0) ? hty.y : 0;
	if (hty.y != 0)
	{
		*p = ft_vec_add(ft_vec_mult_scalar(ray.dir, hty.y), ray.origine);
//		*n = ft_normal_vector(ft_get_norm_cylinder2(data->cy, p));
		return (hty.y);
	}
	return (hty.y);
}

