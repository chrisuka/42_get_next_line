# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 16:57:32 by ikarjala          #+#    #+#              #
#    Updated: 2022/02/21 18:24:39 by ikarjala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= gnl_test
BIN		= ./$(NAME)
CFUNC	= \
get_next_line \
main

ROOT		= ../
SRC_DIR		= $(ROOT)
OBJ_DIR		= ./
SRC			= $(addprefix $(SRC_DIR),$(addsuffix .c,$(CFUNC)))
OBJ			= $(addprefix $(OBJ_DIR),$(addsuffix .o,$(CFUNC)))
INC_DIR		= $(LIB_DIR)
LIB_DIR		= $(ROOT)libft
LIB			= ft
FLAGS		= -Wall -Wextra -Werror -Wimplicit -Wconversion
CC			= clang

## BUILD	====
all: $(NAME)
$(NAME):
	@echo '$(NAME) :: Starting build...'
ifeq (,$(wildcard $(addprefix $(LIB_DIR)/lib,$(addsuffix .a,$(LIB)))))
	@echo '  ! No libraries found, trying to build...'
	make -C $(LIB_DIR)
endif
	$(CC) -c $(FLAGS) $(SRC) -I $(INC_DIR)
	$(CC) -o $(BIN) $(OBJ) -L$(LIB_DIR) -l $(LIB)
	@echo 'Build success!'
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(BIN) $(LIB)
re: fclean all

install: all clean
run: install
	$(BIN) test.txt

## UTILS	====
norme:
	norminette -R CheckForbiddenSourceHeader \
	$(wildcard $(ROOT)get_next_line.c $(ROOT)get_next_line.h)
