/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:03:37 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/02 11:19:28 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "minirt_struct.h"
#include "../libft/libft.h"
#include "../minilibx_opengl/mlx.h"
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

# define BUF_SIZE 1024
# define ESC_KEY 0x35

typedef struct s_image
{
	void		*img;
	char		*ptr;
	int			bpp;
	int			stride;
	int			endian;
}				t_image;

typedef struct		s_data
{
	int				render[2];
	t_ambience		ambience;
	t_cam			*cam;
	t_light			*light;
	t_sphere		*sp;
	t_plane			*pl;
	t_square		*sq;
	t_cylinder		*cy;
	t_triangle		*tr;
	t_image			*image;
	t_ray			ray;
	t_vect3			pix;
	t_vect3			color;
}					t_data;

typedef struct		s_mlx
{
	void	*ptr;
	void	*win;
}				t_mlx;

t_mlx			g_mlx;

void		ft_print_param(t_data *data);

int			ft_strlen_nb(int nb);
int			ft_get_coord(double coord[], char *s, int i);
int			ft_get_color(double color[], char *s, int i);
int			ft_get_dir(double dir[], const char *s, int i);
int			ft_pass_double(char *s, int i);
int			ft_get_render(t_data *data, char *s, int i);
int			ft_get_ambience(t_data *data, char *s, int i);
int			ft_ambience_and_res(t_data *data, char *s, int i);
int			ft_get_cam(t_data *dat, char *s, int i);
int			ft_get_light(t_data *data, char *s, int i);
int			ft_cam_and_light(t_data *data, char *s, int i);
int			ft_check_valid_obj(char *s, int i);
int			ft_obj_is_sphere(t_data *data, char *s, int i);
int			ft_obj_is_plane(t_data *data, char *s, int i);
int			ft_objet(t_data *data, char *s, int i);
int			ft_check_file(t_data *data, char *s);
int			ft_obj_is_square(t_data *data, char *s, int i);
int			ft_obj_is_cylinder(t_data *data, char *s, int i);
int			ft_obj_is_triangle(t_data *data, char *s, int i);
long		ft_get_color_hexa(int color[]);
char		*ft_read_file(char *av);
int			esc_key(int key, void *p);
int			ft_set_color(t_vect3 c);
int			close_window(int button,int x,int y, void *p);
void		ft_new_img(t_data *data);
void		ft_put_pixel_to_img(int x, int y, long color, t_data *data);
void		ft_set_ori(t_vect3 *pos, double aux[3]);
t_vect3		ft_vec_div_scalar(t_vect3, double d);
double		ft_get_norm2(t_vect3 v);
t_vect3		ft_normal_vector(t_vect3 v);
t_vect3		ft_vect_multiplication(t_vect3 v1, t_vect3 v2);
t_vect3		ft_vec_add(t_vect3 v1, t_vect3 v2);
t_vect3		ft_vec_diff(t_vect3 v1, t_vect3 v2);
t_vect3		ft_vec_mult_scalar(t_vect3 v1, double d);
double		ft_dot_product(t_vect3 a, t_vect3 b);
t_vect3		ft_cross_product(t_vect3 a, t_vect3 b);
int			ft_pixel_ray_sp(t_ray ray, t_sphere *sp, t_vect3 *v, t_vect3 *n);
void		ft_check_abs_value(t_vect3 *pixel);
double		ft_to_radian(double degre);
double		ft_distance(t_vect3 a, t_vect3 b);
t_vect3		ft_create_vector(const double x, const double y, const double z);
t_vect3		ft_sub_vector(t_vect3 a, t_vect3 b);
void		ft_init(t_data *data);
int			ft_malloc_data(t_data *data);
void		ft_draw(t_data *data);
double		ft_pixel_ray_pl(t_ray ray, t_plane *pl, t_vect3 *n, t_vect3 *p);
double		ft_intersection_ray_sp(t_ray ray, t_sphere *sp, t_vect3 *p, t_vect3 *n);
int			ft_for_each_sp(t_ray ray, t_data *data, t_vect3 *v, t_vect3 *n);
int			ft_intersection_ray_cy(t_ray ray, t_cylinder *cy, t_vect3 *p, t_vect3 *n);
t_vect3		ft_get_pixel_color(t_data *data, t_vect3 p, t_vect3 n);
void		ft_reset_vect(t_data *data);
double		ft_intersection_ray_pl(t_ray ray, t_plane *pl,
			t_vect3 *p, t_vect3 *n);
#endif
