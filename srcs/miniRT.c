/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:25:31 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/03 15:51:49 by lmoulin          ###   ########.fr       */
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
	data->sp = data->sp->next;
//	data->pl = data->pl->next;
	printf("%d\n", data->pl->rank);
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
