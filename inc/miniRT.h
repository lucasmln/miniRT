/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:13:58 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/20 18:18:17 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "miniRT_struct.h"
#include <stdio.h>
# define BUF_SIZE 1024
/*
 ** ft_parse_utils
 */
int		ft_strlen_nb(int nb);
int		ft_get_coord(double coord[], char *s, int i);
int		ft_get_color(int color[], char *s, int i);
int		ft_get_dir(double dir[], const char *s, int i);
int		ft_pass_double(char *s, int i);
/*
 **	ft_parse_block_1
 */
int		ft_get_render(t_data *data, char *s, int i);
int		ft_get_ambience(t_data *data, char *s, int i);
int		ft_ambience_and_res(t_data *data, char *s, int i);
/*
 ** ft_parse_block_2
 */
int		ft_get_cam(t_data *data, char *s, int i);
int		ft_get_light(t_data *data, char *s, int i);
int		ft_cam_and_light(t_data *data, char *s, int i);
/*
 ** ft_parse_obj_1
 */
int		ft_check_valid_obj(char *s, int i);
int		ft_obj_is_sphere(t_data *data, char *s, int i);
int		ft_obj_is_plane(t_data *data, char *s, int i);
int		ft_objet(t_data *data, char *s, int i);
int		ft_check_file(t_data *data, char *s);
/*
 ** ft_parse_obj_2
 */
int		ft_obj_is_square(t_data *data, char *s, int i);
int		ft_obj_is_cylinder(t_data *data, char *s, int i);
int		ft_obj_is_triangle(t_data *data, char *s, int i);
/*
 ** miniRT_utils
 */
int		ft_get_color_hexa(int color[]);
char	*ft_read_file(char *av);
/*
 ** ft_close
 */
int		esc_key(int key, void *p);
int		close_window(int button,int x,int y, void *p);
/*
 ** ft_image
 */
t_img		*ft_new_img(t_mlx mlx, t_data *data);
void	put_pixel_to_img(int x, int y, int color, t_data *data);
#endif
