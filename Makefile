# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgontier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 12:02:19 by tgontier          #+#    #+#              #
#    Updated: 2020/01/18 06:40:32 by tgontier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME			= miniRT

SRCS_LIST		= \
					main.c \
					parser.c \
					parse_shapes.c \
					parse_helpers.c \
					utils.c \
					calculate_raytracing.c \
					handle_colors.c \
					utils_3.c \
					vectors.c \
					more_vectors.c \
					solve_objects_2.c \
					cameras.c \
					apply_lighting.c \
					solve_objects.c \
					shadows.c \
					handle_keys.c \
					mouse.c \
					move_object.c \
					utils_2.c \
					reflection.c \

SRCS			= $(addprefix ${FOLDER}/, ${SRCS_LIST})

OBJS			= ${SRCS:.c=.o}

HEADER			= includes
FOLDER			= srcs

LIBFT 			= libft
MLX 			= minilibx

CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
LFLAGS			= -L libft -lft

METAL_MLX		= libmlx.dylib -framework Metal -framework AppKit

RM				= rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
				@make -s -C $(MLX)
				@mv $(MLX)/libmlx.dylib .
				@make -s -C $(LIBFT)
				@$(CC) $(CFLAGS) $(LFLAGS) $(METAL_MLX) -I $(HEADER) $(OBJS) -o $(NAME)

%.o: %.c
				@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<

clean:
				@$(RM) $(OBJS)
				@make clean -C $(MLX)
				@make clean -C $(LIBFT)

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) libmlx.dylib
				@$(RM) img.bmp
				@make fclean -C $(LIBFT)

re:				fclean all

.PHONY: 		all fclean clean re
