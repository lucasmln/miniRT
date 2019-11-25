/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:53:28 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/25 14:52:37 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCT_H
# define MINIRT_STRUCT_H

typedef struct		s_vect3
{
	double			x;
	double			y;
	double			z;
}					t_vect3;

typedef struct		s_ambience
{
	double				ratio;
	t_vect3				color;
}					t_ambience;

typedef struct		s_camera
{
	t_vect3				coord;
	t_vect3				dir;
	int					fov;
	struct s_camera		*next;
	struct s_camera		*start;
}					t_cam;

typedef struct		s_light
{
	t_vect3				coord;
	double				ratio;
	t_vect3				color;
	struct s_light		*next;
	struct s_light		*start;
}					t_light;

typedef struct		s_sphere
{
	t_vect3				coord;
	double				diameter;
	t_vect3				color;
	struct s_sphere		*next;
	struct s_sphere		*start;
}					t_sphere;

typedef struct		s_plane
{
	t_vect3				coord;
	t_vect3				dir;
	t_vect3				color;
	struct s_plane		*next;
	struct s_plane		*start;
}					t_plane;

typedef struct		s_square
{
	t_vect3				coord;
	t_vect3				dir;
	double				height;
	t_vect3				color;
	struct s_square		*next;
	struct s_square		*start;
}					t_square;

typedef struct		s_cylinder
{
	t_vect3				coord;
	t_vect3				dir;
	double				diameter;
	double				height;
	t_vect3				color;
	struct s_cylinder	*next;
	struct s_cylinder	*start;
}					t_cylinder;

typedef struct		s_triangle
{
	t_vect3				p_1;
	t_vect3				p_2;
	t_vect3				p_3;
	t_vect3				color;
	struct s_triangle	*next;
	struct s_triangle	*start;
}					t_triangle;

typedef struct		s_ray
{
	t_vect3				origine;
	t_vect3				dir;
}					t_ray;

#endif
