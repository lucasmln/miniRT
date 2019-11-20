/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_print_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:26:41 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/20 15:29:19 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/miniRT.h"
#include "inc/miniRT_struct.h"

void	ft_print_param(t_data *data)
{
	printf("R = %d*%d\n", data->render[0], data->render[1]);
	
	printf("A : ratio = %lf, color = %d, %d, %d\n", data->ambience.ratio,
	data->ambience.color[0], data->ambience.color[1], data->ambience.color[2]);
	
	printf("Cam : coord = %lf, %lf, %lf, dir = %lf, %lf, %lf, fov = %d\n", data->cam->coord[0],
	data->cam->coord[1], data->cam->coord[2],  data->cam->dir[0], data->cam->dir[1], data->cam->dir[2], data->cam->fov);
	
	printf("Light : coord = %lf, %lf, %lf, ratio = %lf, color = %d, %d, %d\n", data->light->coord[0],
	data->light->coord[1], data->light->coord[2], data->light->ratio,
	data->light->color[0], data->light->color[1], data->light->color[2]);

	printf("Sphere : coord = %lf, %lf, %lf, diameter = %lf, dolor =  %d, %d, %d\n", data->sphere->coord[0],
	data->sphere->coord[1], data->sphere->coord[2], data->sphere->diameter,
	data->sphere->color[0], data->sphere->color[1], data->sphere->color[2]);

	printf("Plane : coord = %lf, %lf, %lf, dir = %lf, %lf, %lf, color =  %d, %d, %d\n", data->plane->coord[0],
	data->plane->coord[1], data->plane->coord[2], data->plane->dir[0], data->plane->dir[1], data->plane->dir[2],
	data->plane->color[0], data->plane->color[1], data->plane->color[2]);

	printf("Square : coord = %lf, %lf, %lf, dir = %lf, %lf, %lf, height = %lf, color =  %d, %d, %d\n", data->square->coord[0],
	data->square->coord[1], data->square->coord[2], data->square->dir[0], data->square->dir[1], data->square->dir[2],
	data->square->height, data->square->color[0], data->square->color[1], data->square->color[2]);

	printf("Cylinder : coord = %lf, %lf, %lf, dir = %lf, %lf, %lf, diameter = %lf, height = %lf color =  %d, %d, %d\n",
	data->cylinder->coord[0], data->cylinder->coord[1], data->cylinder->coord[2], data->cylinder->dir[0],
	data->cylinder->dir[1], data->cylinder->dir[2], data->cylinder->diameter, data->cylinder->height, data->cylinder->color[0],
	data->cylinder->color[1], data->cylinder->color[2]);

	printf("Triangle : coord_1 = %lf, %lf %lf, coord_2 = %lf, %lf, %lf, coord_3 = %lf, %lf, %lf, color = %d, %d, %d\n",
	data->triangle->coord_one[0], data->triangle->coord_one[1], data->triangle->coord_one[2], data->triangle->coord_two[0],
	data->triangle->coord_two[1], data->triangle->coord_two[2], data->triangle->coord_three[0], data->triangle->coord_three[1],
	data->triangle->coord_three[2], data->triangle->color[0], data->triangle->color[1], data->triangle->color[2]);
}


