/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:13:58 by lmoulin           #+#    #+#             */
/*   Updated: 2019/11/12 20:49:28 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "miniRT_struct.h"
/*
 ** miniRT_utils
 */
int		ft_strlen_nb(int nb);
int		ft_get_coord(double coord[], char *s, int i);
int		ft_get_color(int color[], char *s, int i);
int		ft_get_dir(double dir[], char *s, int i);
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

#endif
