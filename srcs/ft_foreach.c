/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreach.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:18:57 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/28 21:50:58 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

double		ft_for_each_obj(t_ray ray, t_vect3 *p, t_vect3 *n)
{
	double	res;
	double	tmp;
	t_vect3	tmp_p;
	t_vect3	tmp_n;

	res = 0;
	ft_go_start_lst("all obj");
	if (g_data->sp->next)
		res = ft_for_each_sp(ray, p, n);
	g_data->color = g_data->sp->color;
	g_data->obj = "sp";
	if (g_data->pl->next)
		tmp = ft_for_each_pl(ray, &tmp_p, &tmp_n);
	if (!res || (tmp > 0 && tmp < res && res > 0) || (res <= 0 && tmp > 0))
	{
		res = tmp;
		*p = tmp_p;
		*n = tmp_n;
		g_data->obj = "pl";
		g_data->color = g_data->pl->color;
	}
	if (g_data->tr->next)
		tmp = ft_for_each_tr(ray, &tmp_p, &tmp_n);
	if (!res || (tmp > 0 && tmp < res && res > 0) || (res <= 0 && tmp > 0))
	{
		res = tmp;
		*p = tmp_p;
		*n = tmp_n;
		g_data->obj = "tr";
		g_data->color = g_data->tr->color;
	}
	if (g_data->sq->next)
		tmp = ft_for_each_square(ray, &tmp_p, &tmp_n);
	if (!res || (tmp > 0 && tmp < res && res > 0) || (res <= 0 && tmp > 0))
	{
		res = tmp;
		*p = tmp_p;
		*n = tmp_n;
		g_data->obj = "sq";
		g_data->color = g_data->sq->color;
	}
	if (g_data->cy->next)
		tmp = ft_for_each_cy(ray, &tmp_p, &tmp_n);
	if (!res || (tmp > 0 && tmp < res && res > 0) || (res <= 0 && tmp > 0))
	{
		res = tmp;
		*p = tmp_p;
		*n = tmp_n;
		g_data->obj = "cy";
		g_data->color = g_data->cy->color;
	}
	if (res > EPS)
		return (res);
	return (0);
}
