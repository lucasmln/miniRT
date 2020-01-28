/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 20:18:47 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/21 11:05:09 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	ft_put_scene(void)
{
	mlx_put_image_to_window(g_mlx.ptr, g_mlx.win, g_data->image->img, 0, 0);
	mlx_key_hook(g_mlx.win, get_key, 0);
	mlx_hook(g_mlx.win, 17, 0, close_window, g_mlx.win);
	mlx_loop(g_mlx.ptr);
}

int		main(int ac, char **av)
{
	char	*file;
	int		len_name;

	if (ac <= 1 || ac >= 4)
		ft_print_error(-6);
	ft_malloc_data();
	len_name = 0;
	while (av[1][len_name] && av[1][len_name] != '.')
		len_name++;
	if (ft_strcmp(&av[1][len_name], ".rt"))
		ft_print_error(-2);
	file = ft_read_file(av[1]);
	if (ft_check_file(file) == -1)
		ft_print_error(-3);
	if (!(g_mlx.ptr = mlx_init()))
		ft_print_error(-4);
	if (!(g_mlx.win = mlx_new_window(g_mlx.ptr, g_data->render[0],
		g_data->render[1], "miniRT")))
		ft_print_error(-5);
	ft_create_all_img();
	if ((g_data->image = g_data->image->next) && ac == 2)
		ft_put_scene();
	else if (ac == 3 && !(ft_strcmp(av[2], "-save")))
		ft_create_bmp(av[1], len_name);
	return (0);
}
