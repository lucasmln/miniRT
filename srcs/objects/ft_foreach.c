/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreach.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:18:57 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/29 17:16:05 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void		ft_get_type_obj_inter(int type_obj)
{
	if (type_obj == 1)
	{
		g_data->obj = "pl";
		g_data->color = g_data->pl->color;
	}
	else if (type_obj == 2)
	{
		g_data->obj = "tr";
		g_data->color = g_data->tr->color;
	}
	else if (type_obj == 3)
	{
		g_data->obj = "sq";
		g_data->color = g_data->sq->color;
	}
	else if (type_obj == 4)
	{
		g_data->obj = "cy";
		g_data->color = g_data->cy->color;
	}
}

void		ft_switch_inter(double res[], t_vect3 tmp_p_n[], t_vect3 *p,
																	t_vect3 *n)
{
	res[0] = res[1];
	*p = tmp_p_n[0];
	*n = tmp_p_n[1];
	ft_get_type_obj_inter(res[2]);
}

void		ft_for_each_2(t_ray ray, t_vect3 *p, t_vect3 *n, double res[])
{
	t_vect3		tmp_p;
	t_vect3		tmp_n;

	res[0] = -1;
	res[2] = 0;
	ft_go_start_lst("all obj");
	if (g_data->sp->next)
	{
		res[1] = ft_for_each_sp(ray, &tmp_p, &tmp_n);
		if (res[1] > 0)
		{
			res[0] = res[1];
			*p = tmp_p;
			*n = tmp_n;
			g_data->color = g_data->sp->color;
			g_data->obj = "sp";
		}
	}
}
double		ft_for_each_obj(t_ray ray, t_vect3 *p, t_vect3 *n)
{
	double	res[3];
	t_vect3	tmp_p_n[2];

	ft_for_each_2(ray, p, n, res);
	if (g_data->pl->next)
		res[1] = ft_for_each_pl(ray, &tmp_p_n[0], &tmp_p_n[1]);
	if ((res[2] += 1) && (res[0] < EPS || (res[1] > 0 && res[1] < res[0] &&
									res[0] > 0) || (res[0] <= 0 && res[1] > 0)))
		ft_switch_inter(res, tmp_p_n, p, n);
	if (g_data->tr->next)
		res[1] = ft_for_each_tr(ray, &tmp_p_n[0], &tmp_p_n[1]);
	if ((res[2] += 1) && (res[0] < EPS || (res[1] > 0 && res[1] < res[0] &&
									res[0] > 0) || (res[0] <= 0 && res[1] > 0)))
		ft_switch_inter(res, tmp_p_n, p, n);
	if (g_data->sq->next)
		res[1] = ft_for_each_square(ray, &tmp_p_n[0], &tmp_p_n[1]);
	if ((res[2] += 1) && (res[0] < EPS || (res[1] > 0 && res[1] < res[0] &&
									res[0] > 0) || (res[0] <= 0 && res[1] > 0)))
		ft_switch_inter(res, tmp_p_n, p, n);
	if (g_data->cy->next)
		res[1] = ft_for_each_cy(ray, &tmp_p_n[0], &tmp_p_n[1]);
	if ((res[2] += 1) >= 0 && (res[0] < EPS || (res[1] > 0 && res[1] < res[0] &&
									res[0] > 0) || (res[0] <= 0 && res[1] > 0)))
		ft_switch_inter(res, tmp_p_n, p, n);
	return (res[0] > EPS ? res[0] : 0);
}
