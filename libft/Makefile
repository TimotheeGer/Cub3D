# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/31 12:16:56 by tigerber          #+#    #+#              #
#    Updated: 2022/02/10 19:38:47 by tigerber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = libft.a

CC            = gcc
CFLAGS        = -Wall -Wextra -Werror

SRC_DIR        = ./srcs/

CLASSIC_DIR        = classic/
CLASSIC_SRC        = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c \
ft_isascii.c ft_isdigit.c ft_isprint.c ft_memset.c ft_memmove.c \
ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_strchr.c ft_strdup.c ft_split_charset.c \
ft_strlcat.c ft_strlen.c ft_strncmp.c \
ft_strnstr.c ft_strrchr.c ft_strlcpy.c \
ft_tolower.c ft_toupper.c ft_calloc.c \
ft_strtrim.c ft_strjoin.c ft_substr.c ft_split.c ft_strmapi.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \

LST_DIR        = lst/
LST_SRC        = ft_lstnew.c ft_lstadd_front.c ft_lstlast.c ft_lstadd_back.c \
ft_lstclear.c ft_lstiter.c ft_lstsize.c ft_lstdelone.c\


GNL_DIR = gnl/
GNL_SRC = get_next_line.c get_next_line_utils.c \

LST            = $(addprefix $(LST_DIR),$(LST_SRC))
CLASSIC        = $(addprefix $(CLASSIC_DIR),$(CLASSIC_SRC))
GNL            = $(addprefix $(GNL_DIR),$(GNL_SRC))
FILES        = $(CLASSIC) $(GNL) $(LST)

SRC            = $(addprefix $(SRC_DIR),$(FILES))

OBJ_DIR        = ./obj/
OBJ            = $(addprefix $(OBJ_DIR),$(FILES:.c=.o))

INC            = ./includes/
INCLUDES    = -I $(INC)

.PHONY: clean fclean re all

all: $(NAME)

$(NAME): obj $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

obj:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)$(PF_DIR)
	mkdir -p $(OBJ_DIR)$(LST_DIR)
	mkdir -p $(OBJ_DIR)$(GNL_DIR)
	mkdir -p $(OBJ_DIR)$(CLASSIC_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re:	fclean all
