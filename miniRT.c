/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:25:31 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/21 17:03:18 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minirt.h"
#include "libft/libft.h"
#include "minilibx_opengl/mlx.h"



void	ft_init(t_data *data)
{
	data->cam->next = NULL;
	data->cam->start = data->cam;
	data->light->next = NULL;
	data->light->start = data->light;
	data->sphere->next = NULL;
	data->sphere->start = data->sphere;
	data->plane->next = NULL;
	data->plane->start = data->plane;
	data->square->next = NULL;
	data->square->start = data->square;
	data->cylinder->next = NULL;
	data->cylinder->start = data->cylinder;
	data->triangle->next = NULL;
	data->cylinder->start = data->cylinder;
}

int		ft_malloc_data(t_data	*data)
{
	if (!(data->cam = malloc(sizeof(t_cam) * 1)))
		return (-1);
	if (!(data->light = malloc(sizeof(t_light) * 1)))
		return (-1);
	if (!(data->sphere = malloc(sizeof(t_sphere) * 1)))
		return (-1);
	if (!(data->plane = malloc(sizeof(t_plane) * 1)))
		return (-1);
	if (!(data->square = malloc(sizeof(t_square) * 1)))
		return (-1);
	if (!(data->cylinder = malloc(sizeof(t_cylinder) * 1)))
		return (-1);
	if (!(data->triangle = malloc(sizeof(t_triangle) * 1)))
		return (-1);
	return (0);
}

int		main(int ac, char **av)
{
	char	*file;
	int		*render;
	t_data	*data;
	int		color;

	if (!(data = malloc(sizeof(struct s_data) * 1)))
		return (0);
	if (!(g_mlx.mlx_ptr = malloc(sizeof(void*) * 1)))
		return (0);
	if (!(g_mlx.win_ptr = malloc(sizeof(void*) * 1)))
		return (0);
	if (ft_malloc_data(data) == -1)
		return (0);
	file = ft_read_file(av[1]);
	if (ft_check_file(data, file) == -1)
	{
		printf("erreur file\n");
		return (-1);
	}
//	ft_print_param(data);
	int	x = 0, y = 0;

	if ((g_mlx.mlx_ptr = mlx_init()) == NULL)
		return (-1);
	if ((g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, data->render[0], data->render[1], "miniRT")) == NULL)
		return (-1);
/*	data->img->image = */ft_new_img(g_mlx, data);
	printf("%s\n", data->img->image);
	while (x < data->render[1])
	{
		y = 0;
		while (y < data->render[0])
		{
			if (y == x)
				put_pixel_to_img(x, y, ft_get_color_hexa(data->sphere->color), data);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, data->img->image, 0, 0);
	mlx_key_hook(g_mlx.win_ptr, esc_key, 0);
	mlx_mouse_hook(g_mlx.win_ptr, close_window, 0);
	mlx_loop(g_mlx.mlx_ptr);
	return (0);
}
