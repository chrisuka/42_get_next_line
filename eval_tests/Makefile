# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 16:57:32 by ikarjala          #+#    #+#              #
#    Updated: 2022/04/05 16:50:58 by ikarjala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= gnl_test
BIN		= ./$(NAME)
CFUNC	= \
get_next_line

ROOT		= ../
SRC_DIR		= $(ROOT)
OBJ_DIR		= ./
INC_DIR		= $(ROOT)
SRC			= $(addprefix $(SRC_DIR),$(addsuffix .c,$(CFUNC))) ./main.c
OBJ			= $(addprefix $(OBJ_DIR),$(addsuffix .o,$(CFUNC))) ./main.o
INC			= $(addprefix -I ,$(INC_DIR))
LIB_DIR		= $(ROOT)libft
LIB			= ft
FLAGS		= -Wall -Wextra -Werror -Wimplicit -Wconversion -ggdb
CC			= clang

CMD_NORME	= norminette -R CheckForbiddenSourceHeader
42TEST		= 42filechecker

## BUILD	====
all: $(NAME)
$(NAME):
	@echo '$(NAME) :: Starting build...'
ifeq (,$(wildcard $(addprefix $(LIB_DIR)/lib,$(addsuffix .a,$(LIB)))))
	@echo '  ! No libraries found, trying to build...'
	make -C $(LIB_DIR)
endif
	$(CC) -c $(FLAGS) $(SRC) $(INC)
	$(CC) -o $(BIN) $(OBJ) -L$(LIB_DIR) -l $(LIB)
	@echo 'Build success!'
clean:
	rm -f $(OBJ)
lclean:
	make -C $(LIB_DIR) fclean
fclean: clean
	rm -f $(BIN)
re: fclean all

lib:
	@echo '$(LIB_DIR)/$(LIB) :: Building libraries...'
	make -C $(LIB_DIR) re
run: re clean
	@clear
	$(BIN) testfiles/hello.txt

test: fclean
	bash $(42TEST)
## UTILS	====
norme:
	$(CMD_NORME) $(ROOT)get_next_line.c $(ROOT)get_next_line.h
	$(CMD_NORME) $(LIB_DIR)/*.c $(LIB_DIR)/libft.h

unpack:
	ln -f ft_debugtools.h.test ft_debugtools.h
	ln -f main.c.test main.c
