# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/19 15:50:41 by lmoulin           #+#    #+#              #
#    Updated: 2020/01/19 16:03:14 by lmoulin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME =	miniRT

DIR_SRCS =		./srcs/

SRC = 		image_window/ft_close.c image_window/ft_create_bmp.c \
			image_window/ft_image.c \
			\
			math_vector/ft_calcul_vect.c math_vector/ft_calcul_vect2.c \
			math_vector/ft_maths.c \
			\
			objects/ft_cylinder.c objects/ft_foreach.c objects/ft_plane.c \
			objects/ft_sphere.c objects/ft_square.c objects/ft_triangle.c \
			\
			parse/ft_parse_block_1.c parse/ft_parse_block_2.c \
			parse/ft_parse_cylinder.c parse/ft_parse_plane.c \
			parse/ft_parse_sphere.c parse/ft_parse_square.c \
			parse/ft_parse_triangle.c parse/ft_parse_utils.c \
			parse/ft_parse_utils_2.c \
			\
			raytrace/ft_draw.c raytrace/ft_draw_2.c raytrace/ft_effect.c \
			raytrace/ft_draw_utils.c \
			\
			utils/ft_init.c utils/minirt_utils.c utils/ft_utils_2.c \
			\
			minirt.c

OBJS =	$(SRCS:.c=.o)

SRCS =	$(addprefix $(DIR_SRCS), $(SRC))

CC =	gcc

FRAME = 	-framework OpenGL -framework AppKit

LMINX =		-I /usr/local/include -L /usr/local/lib -lmlx

CFLAGS =	-Wall -Wextra -Werror

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
	gcc $(FRAME) $(CFLAGS) $(LMINX) -o $(NAME) $(OBJS)

clean:
	rm -f srcs/*.o srcs/*/*.o
fclean: clean
	rm -f $(NAME)
re: fclean all
