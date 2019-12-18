/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreach.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:18:57 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/18 15:50:47 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

double		ft_for_each_obj(t_ray ray, t_data *data, t_vect3 *p, t_vect3 *n)
{
	double	res;
	double	tmp;
	t_vect3	tmp_p;
	t_vect3	tmp_n;

	ft_go_start_lst(data, "all obj");
	if (data->sp->next)
		res = ft_for_each_sp(ray, data, p, n);
	data->color = data->sp->color;
	data->obj = "sp";
	if (data->pl->next)
		tmp = ft_for_each_pl(ray, data, &tmp_p, &tmp_n);
	if ((tmp > 0 && tmp < res && res > 0) || (res <= 0 && tmp > 0))
	{
		res = tmp;
		*p = tmp_p;
		*n = tmp_n;
		data->obj = "pl";
		data->color = data->pl->color;
	}
	if (data->tr->next)
		tmp = ft_for_each_tr(ray, data, &tmp_p, &tmp_n);
	if ((tmp > 0 && tmp < res && res > 0) || (res <= 0 && tmp > 0))
	{
		res = tmp;
		*p = tmp_p;
		*n = tmp_n;
		data->obj = "tr";
		data->color = data->tr->color;
	}
	if (data->sq->next)
		tmp = ft_for_each_square(ray, data, &tmp_p, &tmp_n);
	if ((tmp > 0 && tmp < res && res > 0) || (res <= 0 && tmp > 0))
	{
		printf("tmp = %lf\n", tmp);
		res = tmp;
		*p = tmp_p;
		*n = tmp_n;
		data->obj = "tr";
		data->color = data->sq->color;
	}
	if (res > EPS)
		return (res);
	return (0);
}

