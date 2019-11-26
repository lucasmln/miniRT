/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:53:28 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/26 17:27:55 by lmoulin          ###   ########.fr       */
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
	int					rank;
}					t_cam;

typedef struct		s_light
{
	t_vect3				coord;
	double				ratio;
	t_vect3				color;
	struct s_light		*next;
	int					rank;
}					t_light;

typedef struct		s_sphere
{
	t_vect3				coord;
	double				diameter;
	t_vect3				color;
	struct s_sphere		*next;
	int					rank;
}					t_sphere;

typedef struct		s_plane
{
	t_vect3				coord;
	t_vect3				dir;
	t_vect3				color;
	struct s_plane		*next;
	int					rank;
}					t_plane;

typedef struct		s_square
{
	t_vect3				coord;
	t_vect3				dir;
	double				height;
	t_vect3				color;
	struct s_square		*next;
	int					rank;
}					t_square;

typedef struct		s_cylinder
{
	t_vect3				coord;
	t_vect3				dir;
	double				diameter;
	double				height;
	t_vect3				color;
	struct s_cylinder	*next;
	int					rank;
}					t_cylinder;

typedef struct		s_triangle
{
	t_vect3				p_1;
	t_vect3				p_2;
	t_vect3				p_3;
	t_vect3				color;
	struct s_triangle	*next;
	int					rank;
}					t_triangle;

typedef struct		s_ray
{
	t_vect3				origine;
	t_vect3				dir;
}					t_ray;

#endif
