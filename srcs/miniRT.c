/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:25:31 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/14 09:48:36 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
void	ft_print_param(t_data *data);

int		main(int ac, char **av)
{
	char	*file;
	int		len_name;

	if (ac <= 1 || ac >= 4)
		ft_print_error(-6);
	if (!(g_data = malloc(sizeof(struct s_data) * 1)))
		ft_print_error(-1);
	if (!(g_mlx.ptr = malloc(sizeof(void*) * 1)))
		ft_print_error(-1);
	if (!(g_mlx.win = malloc(sizeof(void*) * 1)))
		ft_print_error(-1);
	ft_malloc_data();
	len_name = 0;
	while (av[1][len_name] && av[1][len_name] != '.')
		len_name++;
	if (ft_strcmp(&av[1][len_name], ".rt"))
		ft_print_error(-2);
	file = ft_read_file(av[1]);
	ft_init();
	if (ft_check_file(file) == -1)
		ft_print_error(-3);
	if (!(g_mlx.ptr = mlx_init()))
		ft_print_error(-4);
	if (!(g_mlx.win = mlx_new_window(g_mlx.ptr, g_data->render[0],
		g_data->render[1], "miniRT")))
		ft_print_error(-5);
	ft_create_all_img();
	if (ac == 2)
		ft_put_scene();
	else if (ac == 3 && !(ft_strcmp(av[2], "-save")))
		ft_create_bmp(av[1], len_name);
	return (0);
}

/**
**int		get_coord_mouse(int button, int x, int y, void *p)
**{
**	int		save_rank;
**
**	if (x >= data->render[0] - 100 && x <= data->render[0] - 80 && y <= 50
**		&& y >= 45)
**	{
**		save_rank = data->cam->rank;
**		data->cam = data->cam->next;
**		while (data->cam->next->rank != save_rank)
**			data->cam = data->cam->next;
**		ft_put_scene();
**	}
**	if (x >= data->render[0] - 20 && x <= data->render[0] && y <= 50 && y >= 45)
**	{
**		data->cam = data->cam->next;
**		ft_put_scene();
**	}
**	printf("Mouse in Win1, button %d at %dx%d.\n", button, x, y);
**	return (0);
**}
**/

void	ft_put_scene(void)
{
	mlx_put_image_to_window(g_mlx.ptr, g_mlx.win, g_data->image->img, 0, 0);
	mlx_key_hook(g_mlx.win, get_key, 0);
/*
** mlx_mouse_hook(g_mlx.win, get_coord_mouse, 0);
**/
	mlx_hook(g_mlx.win, 17, 0, close_window, g_mlx.win);
	mlx_loop(g_mlx.ptr);
}
