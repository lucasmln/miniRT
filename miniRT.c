/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:25:31 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/13 16:16:49 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft/libft.h"
#include "minilibx_opengl/mlx.h"
#include <stdio.h>
#define BUF_SIZE 1024


char	*ft_read_file(char *av)
{
	int		ret;
	int		fd;
	int		size;
	char	buf[BUF_SIZE + 1];
	char	*param;

	fd = open(av, O_RDONLY);
	size = 0;
	while ((ret = read(fd, buf, BUF_SIZE)) > 0)
		size += ret;
	close(fd);
	fd = open(av, O_RDONLY);
	if (!(param = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ret = read(fd, param, size);
	param[size] = '\0';
	return (param);
}
/*
int		ft_get_render(char *s)
{
	int		i;
	int		k;
	int		*render;

	i = 0;
	k = 0;
	if (!(render = malloc(sizeof(int) * 2)) || !s)
		return (NULL);
	while (s[i] && s[i] != 'R')
		i++;
	if (s[i] != 'R')
		return (NULL);
	i++;
	while (k < 2)
	{
		while (s[i] == ' ')
			i++;
		if (s[i] <= '0' || s[i] >= '9')
			return (NULL);
		render[k] = ft_atoi(&s[i]);
		k++;
	}
	return (render);
}
*/
void	ft_print_param(t_data *data)
{
	printf("R = %d*%d\n", data->render[0], data->render[1]);
	
	printf("A : ratio = %lf, color = %d, %d, %d\n", data->ambience.ratio,
	data->ambience.color[0], data->ambience.color[1], data->ambience.color[2]);
	
	printf("Cam : coord = %lf, %lf, %lf, dir = %lf, %lf, %lf\n", data->cam->coord[0],
	data->cam->coord[1], data->cam->coord[2],  data->cam->dir[0], data->cam->dir[1], data->cam->dir[2]);
	
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
	unsigned int	color;
	t_mlx	mlx;

	if (!(data = malloc(sizeof(struct s_data) * 1)))
		return (0);
	if (ft_malloc_data(data) == -1)
		return (0);
	file = ft_read_file(av[1]);
	if (ft_check_file(data, file) == -1)
	{
		printf("erreur file\n");
		return (-1);
		}
	ft_print_param(data);
/*	if ((mlx.mlx_ptr = mlx_init()) == NULL)
		return (-1);
	if ((mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, render[0], render[1], "miniRT")) == NULL)
		return (-1);
	color = 0x255;
	color = color * 100 + 0x255;
	color = color * 100 + 0x255;
	int	save;
	k = 0;
	while (i < render[0])
	{	
	k = 0;		while (k < render[1])
		{
			save = mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, k, i, 0xffcc99);
			k++;
		}
//		i++;
//	}
	mlx_loop(mlx.mlx_ptr);
	*/
	return (0);
}
