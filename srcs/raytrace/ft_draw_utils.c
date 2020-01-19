/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 15:00:33 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/19 15:01:21 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void		ft_pix_cmp(t_vect3 *max_pix, t_vect3 *pix)
{
	if (max_pix->x > pix->x)
		pix->x = max_pix->x;
	if (max_pix->y > pix->y)
		pix->y = max_pix->y;
	if (max_pix->z > pix->z)
		pix->z = max_pix->z;
}

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
