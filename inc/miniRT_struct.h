/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:12:06 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/20 18:36:09 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCT_H
#define MINIRT_STRUCT_H

typedef struct		s_ambience
{
	double				ratio;
	int					color[3];
}					t_ambience;

typedef struct		s_camera
{
	double				coord[3];
	double				dir[3];
	int					fov;
	struct s_camera		*next;
	struct s_camera		*start;
}					t_cam;

typedef struct		s_light
{
	double				coord[3];
	double				ratio;
	int					color[3];
	struct s_light		*next;
	struct s_light		*start;
}					t_light;

typedef struct		s_sphere
{
	double				coord[3];
	double				diameter;
	int					color[3];
	struct s_sphere		*next;
	struct s_sphere		*start;
}					t_sphere;

typedef struct		s_plane
{
	double				coord[3];
	double				dir[3];
	int					color[3];
	struct s_plane		*next;
	struct s_plane		*start;
}					t_plane;

typedef struct		s_square
{
	double				coord[3];
	double				dir[3];
	double				height;
	int					color[3];
	struct s_square		*next;
	struct s_square		*start;
}					t_square;

typedef struct		s_cylinder
{
	double				coord[3];
	double				dir[3];
	double				diameter;
	double				height;
	int					color[3];
	struct s_cylinder	*next;
	struct s_cylinder	*start;
}					t_cylinder;

typedef struct		s_triangle
{
	double				coord_one[3];
	double				coord_two[3];
	double				coord_three[3];
	int					color[3];
	struct s_triangle	*next;
	struct s_triangle	*start;
}					t_triangle;

typedef struct		s_image
{
	void		*image;
	char		*ptr;
	int			bpp;
	int			stride;
	int			endian;
}					t_img;

typedef struct		s_data
{
	int			render[2];
	t_ambience	ambience;
	t_cam		*cam;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_square	*square;
	t_cylinder	*cylinder;
	t_triangle	*triangle;
	t_img		*img;

}					t_data;

typedef struct		s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}					t_mlx;

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

#endif
