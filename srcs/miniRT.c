/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:25:31 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/22 18:47:06 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int		main(int ac, char **av)
{
	char	*file;
	int		len_name;

	if (!(data = malloc(sizeof(struct s_data) * 1)))
		return (0);
	if (!(g_mlx.ptr = malloc(sizeof(void*) * 1)))
		return (0);
	if (!(g_mlx.win = malloc(sizeof(void*) * 1)))
		return (0);
	if (ft_malloc_data(data) == -1)
		return (0);
	len_name = 0;
	while (av[1][len_name] && av[1][len_name] != '.')
		len_name++;
	if (ft_strcmp(&av[1][len_name], ".rt"))
		return (0);
	file = ft_read_file(av[1]);
	ft_init(data);
	if (ft_check_file(data, file) == -1)
	{
		printf("erreur file\n");
		return (-1);
	}
/*	printf("rank sq = %d, rank tr1 = %d, rank tr2 = %d\n", data->sq->rank, data->sq->tr->rank, data->sq->tr->next->rank);
	printf("tr1 p_1: x = %lf, y = %lf, z = %lf\n", data->sq->tr->p_1.x, data->sq->tr->p_1.y, data->sq->tr->p_1.z);
	printf("tr1 p_2: x = %lf, y = %lf, z = %lf\n", data->sq->tr->p_2.x, data->sq->tr->p_2.y, data->sq->tr->p_2.z);
	printf("tr1 p_3: x = %lf, y = %lf, z = %lf\n\n", data->sq->tr->p_3.x, data->sq->tr->p_3.y, data->sq->tr->p_3.z);
	data->sq->tr = data->sq->tr->next;
	printf("tr1 p_1: x = %lf, y = %lf, z = %lf\n", data->sq->tr->p_1.x, data->sq->tr->p_1.y, data->sq->tr->p_1.z);
	printf("tr1 p_2: x = %lf, y = %lf, z = %lf\n", data->sq->tr->p_2.x, data->sq->tr->p_2.y, data->sq->tr->p_2.z);
	printf("tr1 p_3: x = %lf, y = %lf, z = %lf\n", data->sq->tr->p_3.x, data->sq->tr->p_3.y, data->sq->tr->p_3.z);

	printf("%lf = ratio_trans\n", data->sq->ratio_trans);
	printf("%d = trans\n", data->sp->next->trans);
*/	if (!(g_mlx.ptr = mlx_init()))
		return (0);
	if (!(g_mlx.win = mlx_new_window(g_mlx.ptr, data->render[0],
		data->render[1], "miniRT")))
		return (0);
	ft_set_obj_coord(data);
	ft_new_img(data);
	ft_draw(data);
	if (ac == 2)
		ft_put_scene();
	else if (ac == 3 && !(ft_strcmp(av[2], "-save")))
		ft_create_bmp(av[1], len_name, data);
	return (0);
}

int		get_coord_mouse(int button, int x, int y, void *p)
{
	int		save_rank;

	if (x >= data->render[0] - 100 && x <= data->render[0] - 80 && y <= 50
		&& y >= 45)
	{
		save_rank = data->cam->rank;
		data->cam = data->cam->next;
		while (data->cam->next->rank != save_rank)
			data->cam = data->cam->next;
		ft_put_scene();
	}
	if (x >= data->render[0] - 20 && x <= data->render[0] && y <= 50 && y >= 45)
	{
		data->cam = data->cam->next;
		ft_put_scene();
	}
	printf("Mouse in Win1, button %d at %dx%d.\n", button, x, y);
	return (0);
}

void	ft_put_scene(void)
{

	mlx_put_image_to_window(g_mlx.ptr, g_mlx.win, data->image->img, 0, 0);
//	mlx_string_put(g_mlx.ptr, g_mlx.win, data->render[0] - 100, 50, 0xff0000, "<== camera ==>");
	mlx_key_hook(g_mlx.win, get_key, 0);
	mlx_mouse_hook(g_mlx.win, get_coord_mouse, 0);
//	mlx_key_hook(g_mlx.win, esc_key, 0);
	mlx_hook(g_mlx.win, 17, 0, close_window, g_mlx.win);
	mlx_loop(g_mlx.ptr);
}
