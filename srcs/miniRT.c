/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:25:31 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/26 19:49:29 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int		main(int ac, char **av)
{
	char	*file;
	int		*render;
	t_data	*data;

	if (!(data = malloc(sizeof(struct s_data) * 1)))
		return (0);
	if (!(g_mlx.ptr = malloc(sizeof(void*) * 1)))
		return (0);
	if (!(g_mlx.win = malloc(sizeof(void*) * 1)))
		return (0);
	if (ft_malloc_data(data) == -1)
		return (0);
	file = ft_read_file(av[1]);
	ft_init(data);
	if (ft_check_file(data, file) == -1)
	{
		printf("erreur file\n");
		return (-1);
	}
/*	printf("cam 1 x = %lf, y = %lf, z = %lf, rank = %d\n\n", data->cam->coord.x, data->cam->coord.y, data->cam->coord.z, data->cam->rank);
	data->cam = data->cam->next;
	while (data->cam->rank != 1)
	{
		printf("cam %d x = %lf, y = %lf, z = %lf\n\n", data->cam->rank, data->cam->coord.x, data->cam->coord.y, data->cam->coord.z);
		data->cam = data->cam->next;
	}
	while (data->light->rank != 1)
	{
		printf("light %d x = %lf, y = %lf, z = %lf\n\n", data->light->rank, data->light->coord.x, data->light->coord.y, data->light->coord.z);
		data->cam = data->cam->next;
	}
	data->light = data->light->next;
	printf("cam 1 x = %lf, y = %lf, z = %lf, rank = %d\n\n", data->cam->coord.x, data->cam->coord.y, data->cam->coord.z, data->cam->rank);
//	ft_print_param(data);*/
	data->sp = data->sp->next;
	printf("%d\n", data->sp->rank);
	if (!(g_mlx.ptr = mlx_init()))
		return (0);
	if (!(g_mlx.win = mlx_new_window(g_mlx.ptr, data->render[0], data->render[1], "miniRT")))
		return (0);

	ft_new_img(data);
	ft_draw(data);
	mlx_put_image_to_window(g_mlx.ptr, g_mlx.win, data->image->img, 0, 0);
	mlx_key_hook(g_mlx.win, esc_key, 0);
	mlx_hook(g_mlx.win, 17, 0, close_window, g_mlx.win);
	mlx_loop(g_mlx.ptr);
	return (0);
}
