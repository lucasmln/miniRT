/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:20:57 by lmoulin           #+#    #+#             */
/*   Updated: 2019/12/17 20:16:04 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int		close_window(int button, int x, int y, void *p)
{
	mlx_destroy_window(g_mlx.ptr, g_mlx.win);
	exit(0);
}

int		get_key(int key, void *p)
{
	if (key == ESC_KEY)
	{
		mlx_destroy_window(g_mlx.ptr, g_mlx.win);
		exit(0);
	}
	return (0);
}

void	ft_print_error(int err_nb)
{
	if (err_nb == -1)
		write(STDERR_FILENO, "Error : echec de malloc", 23);
	if (err_nb == -2)
		write(STDERR_FILENO, "Error : nom de fichier invalide", 31);
	if (err_nb == -3)
		write(STDERR_FILENO, "Error : description de scene invalide", 37);
	if (err_nb == -4)
		write(STDERR_FILENO, "Error : initialisation mlx fail", 31);
	if (err_nb == -5)
		write(STDERR_FILENO, "Error : creation window fail", 28);
	if (err_nb == -6)
		write(STDERR_FILENO, "Error : mauvais nombre d'arguments", 34);
	if (err_nb == -7)
		write(STDERR_FILENO, "Error : open bmp fail", 21);
	if (err_nb == -8)
		write(STDERR_FILENO, "Error : creation image fail", 27);
	exit(err_nb);
}
