# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/26 15:50:08 by ldrieu            #+#    #+#              #
#    Updated: 2021/04/08 12:14:50 by tigerber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC =	./srcs/test.c \
		./srcs/parse.c \
		./srcs/parse_utils.c \
		./srcs/lst_utils.c \
		./srcs/checkvaluerfcmap.c \
		./srcs/checkpath.c \
		./srcs/checkmap.c \
		./srcs/checkmap_utils.c \
		./srcs/checkmap_utils2.c \

OBJS=		${SRC:.c=.o}
HEAD=		-I includes -I libft/includes -I mlx
CC=			gcc
CFLAGS=		-Wall -Werror -Wextra
LIBFT_DIR=	libft
MLX_DIR=	mlx
LDFLAGS=	-L ${LIBFT_DIR} -L ${MLX_DIR}
LIBS=		-lm -lft -lmlx -lXext -lX11
DEFINE_DEFAULT= -D PROJECT_NAME="${NAME}"

%.o:%.c
		${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}
$(NAME):	${OBJS}
		make -C ${LIBFT_DIR}
		make -C ${MLX_DIR}
		${CC} ${CFLAGS} ${LDFLAGS} ${DEFINE_DEFAULT} ${OBJS} -o ${NAME} ${LIBS}
all:	${NAME}

clean:
		rm -rf ${OBJS}
		make clean -C ${LIBFT_DIR}
		make clean -C ${MLX_DIR}
fclean:	clean
		rm -rf ${NAME}
		make fclean -C ${LIBFT_DIR}
		rm -rf screenshot.bmp
re:	fclean all
.PHONY:	all clean fclean re
