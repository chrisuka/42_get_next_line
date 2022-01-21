# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 16:57:32 by ikarjala          #+#    #+#              #
#    Updated: 2021/12/18 21:15:46 by ikarjala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= gnl_tester
BIN		= ./$(NAME)
CFUNC	= get_next_line main

ROOT		= ../
SRC_DIR		= ./
OBJ_DIR		= ./
SRC			= $(addprefix $(SRC_DIR),$(addsuffix .c,$(CFUNC)))
OBJ			= $(addprefix $(OBJ_DIR),$(addsuffix .o,$(CFUNC)))
INC_DIR		= ./
LIB			=
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


## UTILS -----
git:
	ln -f gitignore.linkme $(ROOT).gitignore
