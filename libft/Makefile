# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgontier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/12 10:58:54 by tgontier          #+#    #+#              #
#    Updated: 2018/10/17 14:07:11 by tgontier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
CC=gcc
CFLAGS=-Wall -Wextra -Werror
RM=rm -f
LDFLAGS=-L.
LDLIBS=-lft
SRC = ft_atof.c \
	ft_atoi.c \
	ft_bzero.c \
	ft_c_to_str.c \
	ft_calloc.c \
	ft_intlen.c \
	ft_is_in_stri.c \
	ft_is_space.c \
	ft_isdigit.c \
	ft_itoa.c \
	ft_lstadd_back.c \
	ft_lstclear.c \
	ft_lstlast.c \
	ft_lstnew.c \
	ft_lstsize.c \
	ft_memalloc.c \
	ft_memcpy.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putchar.c \
	ft_putendl.c \
	ft_putstr_fd.c \
	ft_putstr.c \
	ft_split.c \
	ft_ssplit.c \
	ft_str_c_count.c \
	ft_str_end.c \
	ft_strcat.c \
	ft_strcpy.c \
	ft_strdel.c \
	ft_strequ.c \
	ft_strjoin.c \
	ft_strlen_c.c \
	ft_strlen.c \
	ft_strnew.c \
	ft_substr.c \
	get_next_line.c \

OBJ = $(SRC:.c=.o)
INC = ./inc/

$(NAME): $(OBJ)
		@ar rc $(NAME) $(OBJ)
		@ranlib $(NAME)

%.o: %.c
		@$(CC) -I. -o $@ -c $? $(CFLAGS)

all: $(NAME)

clean:
		@$(RM) $(OBJ)

fclean: clean
		@$(RM) $(NAME)

re: fclean all

.PHONY: clean clean