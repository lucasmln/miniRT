/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 15:59:15 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/30 15:28:53 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define BUF_SIZE 1024
# define ESC_KEY 0x35
# define EPS 0.000001

# include "minirt_struct.h"
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef struct	s_image
{
	void			*img;
	char			*ptr;
	int				bpp;
	int				stride;
	int				endian;
	int				rank;
	struct s_image	*next;
}				t_image;

typedef struct	s_data
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
	t_vect3			tmp_pix;
	t_vect3			color;
	t_inter			inter;
	t_ray			ray_mir;
	t_ray			ray_trans;
	char			*obj;
	double			check_trans;
	int				check_mir;
	int				check;
	char			*file;
}				t_data;

typedef struct	s_mlx
{
	void	*ptr;
	void	*win;
}				t_mlx;

t_mlx		g_mlx;
t_data		*g_data;

/*
 ** image_window
*/

void			ft_change_cam(int key);
void			ft_print_error(int err_nb);
void			ft_create_bmp(char *name, int len_name);
void			ft_new_img();
void			ft_create_all_img(void);
void			ft_put_pixel_to_img(int x, int y, long color);
int				close_window(void);
int				get_key(int key);

/*
 ** math_vector
*/

t_vect3			ft_vec_div_scalar(t_vect3 v1, double d);
double			ft_get_norm2(t_vect3 v);
t_vect3			ft_normal_vector(t_vect3 v);
t_vect3			ft_vect_multiplication(t_vect3 v1, t_vect3 v2);
t_vect3			ft_vec_add(t_vect3 v1, t_vect3 v2);
t_vect3			ft_vec_diff(t_vect3 v1, t_vect3 v2);
t_vect3			ft_vec_mult_scalar(t_vect3 v1, double d);
double			ft_dot_product(t_vect3 a, t_vect3 b);
t_vect3			ft_cross_product(t_vect3 a, t_vect3 b);
t_vect3			ft_sub_vector(t_vect3 a, t_vect3 b);
double			ft_to_radian(double degre);
double			ft_distance(t_vect3 a, t_vect3 b);
double			ft_sqr(double a);
t_vect3			ft_vect_add_scalar(t_vect3 v, double d);

/*
 ** objects
*/

double			ft_for_each_tr(t_ray ray, t_vect3 *p, t_vect3 *n);
double			ft_for_each_obj(t_ray ray, t_vect3 *p, t_vect3 *n);
double			ft_for_each_cy(t_ray ray, t_vect3 *p, t_vect3 *n);
double			ft_for_each_square(t_ray ray, t_vect3 *p, t_vect3 *n);
double			ft_intersection_ray_cy(t_ray ray, t_cylinder *cy);
double			ft_intersection_ray_pl(t_ray ray, t_plane *pl, t_vect3 *p,
																	t_vect3 *n);
double			ft_intersection_ray_sp(t_ray ray, t_sphere *sp, t_vect3 *p,
																	t_vect3 *n);
double			ft_intersection_ray_tr(t_ray ray, t_triangle *tr, t_vect3 *p,
																	t_vect3 *n);
void			ft_create_square_point(t_square *sq);
double			ft_for_each_sp(t_ray ray, t_vect3 *v, t_vect3 *n);
double			ft_for_each_pl(t_ray ray, t_vect3 *p, t_vect3 *n);

/*
 ** parse
*/

int				ft_strlen_nb(int nb);
int				ft_get_coord(double coord[], char *s, int i);
int				ft_get_color(double color[], char *s, int i);
int				ft_get_dir(double dir[], const char *s, int i);
int				ft_pass_double(char *s, int i);
int				ft_get_render(char *s, int i);
int				ft_get_ambience(char *s, int i);
int				ft_ambience_and_res(char *s, int i);
int				ft_get_cam(char *s, int i);
int				ft_get_light(char *s, int i);
int				ft_cam_and_light(char *s, int i);
int				ft_check_valid_obj(char *s, int i);
int				ft_obj_is_sphere(char *s, int i);
int				ft_obj_is_plane(char *s, int i);
int				ft_objet(char *s, int i);
int				ft_check_file(char *s);
int				ft_obj_is_square(char *s, int i);
int				ft_obj_is_cylinder(char *s, int i);
int				ft_obj_is_triangle(char *s, int i);
int				ft_set_ori(t_vect3 *pos, double aux[3], int param);

/*
 **raytrace
*/

t_vect3			ft_raytrace(t_ray ray, int coord[], int nb);
void			ft_draw();
void			ft_check_abs_value(t_vect3 *pixel);
void			ft_reset_values(t_vect3 *pix);
t_vect3			ft_get_pixel_color(t_vect3 p, t_vect3 n);
void			ft_pix_cmp(t_vect3 *max_pix, t_vect3 *pix);
int				ft_check_obj_trans(void);
int				ft_check_mirroir(t_ray ray);
t_vect3			ft_check_transparence(t_ray ray);
int				ft_inter_light(t_vect3 *p, t_vect3 *n);

/*
 ** utils
*/

void			ft_init();
int				ft_malloc_data();
int				ft_init_tr_in_sq(t_square *sq);
double			ft_atod(char *s);
int				ft_atoi(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			ft_go_start_lst(char *lst);
void			ft_go_start_2(char *lst);
void			ft_go_start_3(char *lst);
int				ft_set_color(t_vect3 c);
char			*ft_read_file(char *av);
void			ft_no_leaks(void);
void			ft_no_leaks_6(t_data *tmp);

#endif
