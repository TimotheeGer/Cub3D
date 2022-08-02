# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/26 15:50:08 by ldrieu            #+#    #+#              #
#    Updated: 2022/02/11 13:36:43 by tigerber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
BONUS = cub3D_bonus

CC = clang
CFLAGS = -Wall -Werror -Wextra
HEAD = -I includes -I libft/includes -I mlx
LIBFT_DIR = libft
MLX_DIR = mlx
LDFLAGS = -L ${LIBFT_DIR} -L ${MLX_DIR}
LIBS = -lm -lft -lmlx -lXext -lX11
DEFINE_DEFAULT= -D PROJECT_NAME="${NAME}"

SRC =	./srcs/cub3d.c \
		./srcs/main.c \
		./srcs/parsing/checkvaluerfcmap.c \
		./srcs/parsing/checkpath.c \
		./srcs/parsing/parse_utils.c \
		./srcs/parsing/checkmap.c \
		./srcs/parsing/checkmap_utils.c \
		./srcs/parsing/checkmap_utils2.c \
		./srcs/utils/lst_utils2.c \
		./srcs/utils/lst_utils.c \
		./srcs/utils/utils_plus.c \
		./srcs/raycast/floor.c \
		./srcs/raycast/raycast_two.c \
		./srcs/raycast/raycast.c \
		./srcs/quit.c \
		./srcs/move.c \
		./srcs/mini_map.c

SRC_BONUS =	./srcs_bonus/cub3d_bonus.c \
			./srcs_bonus/main_bonus.c \
			./srcs_bonus/parsing/checkvaluerfcmap_bonus.c \
			./srcs_bonus/parsing/checkpath_bonus.c \
			./srcs_bonus/parsing/parse_utils_bonus.c \
			./srcs_bonus/parsing/checkmap_bonus.c \
			./srcs_bonus/parsing/checkmap_utils_bonus.c \
			./srcs_bonus/parsing/checkmap_utils2_bonus.c \
			./srcs_bonus/utils/lst_utils2_bonus.c \
			./srcs_bonus/utils/lst_utils_bonus.c \
			./srcs_bonus/utils/utils_plus_bonus.c \
			./srcs_bonus/raycast/floor_bonus.c \
			./srcs_bonus/raycast/raycast_two_bonus.c \
			./srcs_bonus/raycast/raycast_bonus.c \
			./srcs_bonus/quit_bonus.c \
			./srcs_bonus/move_bonus.c \
			./srcs_bonus/mini_map_bonus.c

OBJS=		${SRC:.c=.o}

OBJS_BONUS = ${SRC_BONUS:.c=.o}

all :	${NAME}

$(NAME):	${OBJS}
		make -C ${LIBFT_DIR}
		make -C ${MLX_DIR}
		${CC} ${CFLAGS} ${LDFLAGS} ${DEFINE_DEFAULT} ${OBJS} -o ${NAME} ${LIBS}

%.o:%.c
		${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

bonus : ${BONUS}

$(BONUS):	${OBJS_BONUS}
		make -C ${LIBFT_DIR}
		make -C ${MLX_DIR}
		${CC} ${CFLAGS} ${LDFLAGS} ${DEFINE_DEFAULT} ${OBJS_BONUS} -o ${BONUS} ${LIBS}

clean :
		rm -rf ${OBJS}
		rm -rf ${OBJS_BONUS}
		make clean -C ${LIBFT_DIR}
		make clean -C ${MLX_DIR}

fclean : clean
		rm -rf ${NAME}
		rm -rf ${BONUS}
		make fclean -C ${LIBFT_DIR}
		rm -rf screenshot.bmp

re : fclean all

re_bonus : fclean bonus

.PHONY:	all bonus clean fclean re re_bonus
