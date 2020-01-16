/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 15:59:15 by lmoulin           #+#    #+#             */
/*   Updated: 2020/01/14 09:29:35 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define BUF_SIZE 1024
# define ESC_KEY 0x35
# define EPS 0.000001

# include "minirt_struct.h"
# include "../libft/libft.h"
# include "../minilibx_opengl/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef struct		s_image
{
	void			*img;
	char			*ptr;
	int				bpp;
	int				stride;
	int				endian;
	int				rank;
	struct s_image	*next;
}					t_image;

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
	t_pyramide		*py;
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
}					t_data;

typedef struct		s_mlx
{
	void	*ptr;
	void	*win;
}					t_mlx;

t_mlx		g_mlx;
t_data		*g_data;

void		ft_print_param(t_data *data);
int			ft_strlen_nb(int nb);
int			ft_get_coord(double coord[], char *s, int i);
int			ft_get_color(double color[], char *s, int i);
int			ft_get_dir(double dir[], const char *s, int i);
int			ft_pass_double(char *s, int i);
int			ft_get_render(char *s, int i);
int			ft_get_ambience(char *s, int i);
int			ft_ambience_and_res(char *s, int i);
int			ft_get_cam(char *s, int i);
int			ft_get_light(char *s, int i);
int			ft_cam_and_light(char *s, int i);
int			ft_check_valid_obj(char *s, int i);
int			ft_obj_is_sphere(char *s, int i);
int			ft_obj_is_plane(char *s, int i);
int			ft_objet(char *s, int i);
int			ft_check_file(char *s);
int			ft_obj_is_square(char *s, int i);
int			ft_obj_is_cylinder(char *s, int i);
int			ft_obj_is_triangle(char *s, int i);
long		ft_get_color_hexa(int color[]);
char		*ft_read_file(char *av);
int			esc_key(int key, void *p);
int			ft_set_color(t_vect3 c);
int			close_window(int button, int x, int y, void *p);
void		ft_new_img();
void		ft_put_pixel_to_img(int x, int y, long color);
int			ft_set_ori(t_vect3 *pos, double aux[3], int param);
t_vect3		ft_vec_div_scalar(t_vect3 v1, double d);
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
void		ft_init();
int			ft_malloc_data();
void		ft_draw();
double		ft_intersection_ray_sp(t_ray ray, t_sphere *sp, t_vect3 *p,
																	t_vect3 *n);
double		ft_for_each_sp(t_ray ray, t_vect3 *v, t_vect3 *n);
double		ft_intersection_ray_cy(t_ray ray, t_cylinder *cy, t_vect3 *p,
																	t_vect3 *n);
double		ft_intersection_ray_pl(t_ray ray, t_plane *pl, t_vect3 *p,
																	t_vect3 *n);
void		ft_reset_values(t_vect3 *pix);
t_vect3		ft_get_pixel_color(t_vect3 p, t_vect3 n);
t_vect3		ft_raytrace(t_ray ray, int coord[], int nb);
double		ft_for_each_pl(t_ray ray, t_vect3 *p, t_vect3 *n);
int			get_key(int key, void *p);
void		ft_put_scene(void);
void		ft_go_start_2(char *lst);
void		ft_go_start_lst(char *lst);
double		ft_intersection_ray_tr(t_ray ray, t_triangle *tr, t_vect3 *p,
																	t_vect3 *n);
double		ft_for_each_tr(t_ray ray, t_vect3 *p, t_vect3 *n);
double		ft_for_each_obj(t_ray ray, t_vect3 *p, t_vect3 *n);
double		ft_for_each_cy(t_ray ray, t_vect3 *p, t_vect3 *n);
void		ft_vect_swap(t_vect3 *a, t_vect3 *b);
void		ft_check_point(t_vect3 *p1, t_vect3 *p2, t_vect3 *p3);
int			ft_init_tr_in_sq(t_square *sq);
void		ft_create_square_point(t_square *sq);
double		ft_for_each_square(t_ray ray, t_vect3 *p, t_vect3 *n);
double		ft_sqr(double a);
void		ft_create_bmp(char *name, int len_name);
void		ft_set_obj_coord();
void		ft_print_error(int err_nb);
void	ft_create_all_img(void);

#endif
