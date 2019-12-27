/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 12:56:02 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/22 13:13:28 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

double		ft_for_each_cy(t_ray ray, t_data *data, t_vect3 *p, t_vect3 *n)
{
	double	inter;
	double	min;
	int		pos;

	pos = data->cy->rank;
	min = -1;
	ft_go_start_lst(data, "cylinder");
	while (1)
	{
		inter = ft_intersection_ray_cy(ray, data->cy, p, n);
		if (inter != 0)
			if (min == -1 || fmin(inter, min) == inter)
			{
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


int			ft_check_inter(t_ray ray, t_cylinder *cy, double t)
{
	t_vect3		s1;
	t_vect3		s2;
	t_vect3		tmp;

	if (t == -1)
		return (0);
	tmp = ft_vect_add(cy->coord, ft_vec_mult_scalar(ft_normal_vector(cy->dir), cy->height));
}

double		ft_intersection_ray_cy(t_ray ray, t_cylinder *cy, t_vect3 *p, t_vect3 *n)
{
	double		a[7];
	t_vect3		vec[3];

	vec[0] = ft_vec_diff(ray.dir, ft_vec_mult_scalar(ft_normal_vector(cy->dir), ft_dot_product(ray.dir, ft_normal_vector(cy->dir))));
	vec[2] = ft_vec_diff(ray.origine, cy->coord);
	vec[1] = ft_vec_diff(vec[2], ft_vec_mult_scalar(ft_normal_vector(cy->dir), ft_dot_product(vec[2], ft_normal_vector(cy->dir))));
	a[0] = ft_dot_product(vec[0], vec[0]);
	a[1] = ft_dot_product(vec[1], vec[1]) * 2;
	a[2] = ft_dot_product(vec[1], vec[1] - cy->diameter * cy->diameter;
	a[5] = a[1] * a[1] - 4 * a[0] * a[2];
	a[6] = check_circle(ray, cy);
	if (a[5] > 0)
	{
		a[2] = sqrt(a[5]);
		a[3] = (-a[1] + a[2]) / (2 * a[0]);
		a[4] = (-a[1] - a[2]) / (2 * a[0]);

	}



/*
double		ft_intersection_ray_cy(t_ray ray, t_cylinder *cy, t_vect3 *p, t_vect3 *n)
{

// Calcul des coord de *p
	double		dot;
	t_vect3		mult;
	t_vect3		sub1;
	t_vect3		sub2;
	t_vect3		delta_p;

	dot = ft_dot_product(ray.dir, cy->dir);
	mult = ft_vec_mult_scalar(cy->dir, dot);
	sub1 = ft_vec_diff(ray.origine, cy->coord);
	delta_p = ft_vec_diff(ray.origine, cy->coord);
	dot = ft_dot_product(delta_p, cy->dir);
	mult = ft_vec_mult_scalar(cy->dir, dot);
	sub2 = ft_vec_diff(delta_p, mult);
	p->x = ft_dot_product(sub1, sub2);
	p->y = 2 * ft_dot_product(sub1, sub2);
	p->z = ft_dot_product(sub2, sub2) - cy->height;


// Calcul de la distance si l'intersection est visbile
	double		delta;
	double		sqrt_delta;
	double		t0;
	double		t1;
	double		t;

	delta = (p->y * p->y) - (4 * p->x * p->z);
	if (delta < 0)
		return (0);
	sqrt_delta = sqrt(delta);
	t0 = (-p->y + sqrt_delta) / (2 * p->x);
	t1 = (-p->y - sqrt_delta) / (2 * p->x);
	t = (t0 < 0) ? 0 : t0;
	t = (t1 > 0 && t1 < t0) ? t1 : t;


// Calcul de la normal

	t_vect3		scaled;
	t_vect3		b;
	t_vect3		a;
	t_vect3		rv;

	scaled = ft_vec_mult_scalar(ray.dir, t);
	b = ft_vec_diff(ft_vec_add(ray.origine, scaled), cy->coord);
	a = ft_vec_mult_scalar(cy->dir, ft_dot_product(b, cy->dir));
	rv = ft_vec_diff(b, a);
	*n = ft_normal_vector(rv);
	return (t);
}
