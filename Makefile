# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/30 12:15:20 by lmoulin           #+#    #+#              #
#    Updated: 2020/01/30 12:35:25 by lmoulin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =			gcc

FLAGS =			-Wall -Wextra -Werror

RM =			rm -rf

DIR_HEADERS =	./inc/

DIR_SRCS =		./srcs/

DIR_OBJS =		./

LMINX = 	./minilibx_opengl/libmlx.a

FRAME =		-framework OpenGl -framework AppKit


SRC =		image_window/ft_close.c image_window/ft_create_bmp.c \
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
			utils/ft_no_leaks.c \
			\
			minirt.c


SRCS =			$(addprefix $(DIR_SRCS), $(SRC))

COMPIL =		$(FLAGS) $(FRAME)

OBJS =			$(SRCS:.c=.o)

NAME =			miniRT

all:			$(NAME)

$(NAME) :		mlxlib $(OBJS)
				$(CC) $(COMPIL) -I $(DIR_HEADERS) $(OBJS) $(LMINX) -o $(NAME)

%.o: %.c
				@gcc $(FLAGS) -I $(DIR_HEADERS) -c $< -o $@
				@echo "Compiled "$<" successfully!"

bonus:

mlxlib:
	@[ -f $(LMINX) ] || (echo "Make mlx.a" && make -C ./minilibx_opengl/)

norme:
				norminette $(DIR_SRCS)
				norminette $(DIR_HEADERS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all, clean, fclean, re, bonus
