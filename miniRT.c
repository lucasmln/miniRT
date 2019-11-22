/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:25:31 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/22 16:50:47 by lmoulin          ###   ########.fr       */
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

void	ft_put_losange(t_sphere *sp, t_data *data)
{
	int		x;
	int		y;
	int		color;

	x = 0;
	color = ft_get_color_hexa(sp->color);
	while (x < data->render[0])
	{
		y = 0;
		while (y < data->render[1])
		{
			if (fabs(x - sp->coord[0]) + fabs(y - sp->coord[1]) == 50)
				put_pixel_to_img(x, y, color, data);
			y += 1.0;
		}
		x += 1.0;
	}
}

int		ft_distance(int x1, int x2, int y1, int y2)
{
	return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

void	ft_put_sphere(t_sphere *sp, t_data *data)
{
	double		x;
	double		y;
	int			check;
	int			save[3];

	x = sp->coord[0] - sp->diameter;
	save[0] = sp->color[0];
	save[1] = sp->color[1];
	save[2] = sp->color[2];
	while (x <= sp->coord[0] + sp->diameter)
	{
		y = sp->coord[1] - sp->diameter;
		check = 4;
		while (y <= sp->coord[1] + sp->diameter)
		{
				save[0] = sp->color[0];
				save[1] = sp->color[1];
				save[2] = sp->color[2];
				if (sqrt(pow(x - sp->coord[0], 2) + pow(y - sp->coord[1], 2)) <= data->sphere->diameter)
				{
					save[0] = save[0] - ((save[0] * 100 / 255) * (sp->diameter - ft_distance(x, sp->coord[0], y, sp->coord[1]) - sp->diameter) * -1) / 100;
					save[1] = save[1] - ((save[1] * 100 / 255) * (sp->diameter - ft_distance(x, sp->coord[0], y, sp->coord[1]) - sp->diameter) * -1) / 100;
					save[2] = save[2] - ((save[2] * 100 / 255) * (sp->diameter - ft_distance(x, sp->coord[0], y, sp->coord[1]) - sp->diameter) * -1) / 100;
					if (save[0] < 0)
						save[0] = 0;
					if (save[1] < 0)
						save[1] = 0;
					if (save[2] < 0)
						save[2] = 0;
					put_pixel_to_img(x, y, ft_get_color_hexa(save), data);
				}
			y += 1;
		}
		x += 1;
	}
}

void	ft_put_square(t_sphere *sp, t_data *data)
{
	double		x;
	double		y;
	int			k;
	int		color;

	x = sp->coord[0] - 50;
	color = ft_get_color_hexa(sp->color);
	while (x <= sp->coord[0] + 50)
	{
		y = sp->coord[1] - 50;
		while (y <= sp->coord[1] + 50)
		{
			k = -1;
			while (++k * 10 < data->sphere->diameter)
			{
				if (sqrt(pow(x - sp->coord[0], 2) + pow(y - sp->coord[1], 2)) / 10 <= k)
					put_pixel_to_img(x, y, color, data);
				k++;
			}
			y++;
		}
		x++;
	}
}

int		ft_is_on_cam(t_data *data, int x, int y, int z)
{
	
}

int		main(int ac, char **av)
{
	char	*file;
	int		*render;
	t_data	*data;

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
	long	color = 0;

	if ((g_mlx.mlx_ptr = mlx_init()) == NULL)
		return (-1);
	if ((g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, data->render[0], data->render[1], "miniRT")) == NULL)
		return (-1);
	ft_new_img(g_mlx, data);
	color = ft_get_color_hexa(data->square->color);
/*	while (x < data->render[0])
	{
		y = 0;
		while (y < data->render[1])
		{
			put_pixel_to_img(x, y, color, data);
			y++;
		}
		x++;
	}
*/	ft_put_sphere(data->sphere, data);
//	data->sphere->coord[0] += 2 *data->sphere->diameter - 1;
//	ft_put_sphere(data->sphere, data);
//	ft_put_losange(data->sphere, data);
	mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, data->img->image, 0, 0);
	mlx_key_hook(g_mlx.win_ptr, esc_key, 0);
	mlx_hook(g_mlx.win_ptr, 17, 0, &red_cross, g_mlx.mlx_ptr);
	mlx_mouse_hook(g_mlx.win_ptr, close_window, 0);
	mlx_loop(g_mlx.mlx_ptr);
	return (0);
}
