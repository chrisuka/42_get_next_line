# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 16:57:32 by ikarjala          #+#    #+#              #
#    Updated: 2022/02/04 01:13:17 by ikarjala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= gnl_test
BIN		= ./$(NAME)
CFUNC	= \
get_next_line \
main

ROOT		= ../
SRC_DIR		= ./
OBJ_DIR		= ./
SRC			= $(addprefix $(SRC_DIR),$(addsuffix .c,$(CFUNC)))
OBJ			= $(addprefix $(OBJ_DIR),$(addsuffix .o,$(CFUNC)))
INC_DIR		= ./
LIB			= ft
FLAGS		= -Wall -Wextra -Werror -Wimplicit -Wconversion
CC			= clang

all: $(NAME)
$(NAME):
	@echo '$(NAME) :: Starting build...'
	$(CC) -c $(FLAGS) $(SRC) -I $(INC_DIR)
	$(CC) -o $(BIN) $(OBJ)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(BIN) $(LIB)
re: fclean all

install: all clean
run: install
	$(BIN)
