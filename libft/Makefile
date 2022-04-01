# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 16:57:32 by ikarjala          #+#    #+#              #
#    Updated: 2022/04/01 16:09:38 by ikarjala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
BIN		= ./$(NAME)

FUNC_P12	= \
ft_isprint \
ft_strlen \
ft_putchar_fd ft_putchar \
ft_putstr_fd ft_putstr ft_putendl_fd ft_putendl \
ft_putnbr ft_putnbr_fd \
ft_putstr_fd ft_putstr \
\
ft_bzero ft_memset \
ft_memchr \
ft_strdel ft_memdel \
ft_memcpy ft_memmove ft_memdup

FUNC_BONUS	= \
ft_lstinit ft_lstnew \
ft_lstdel ft_lstdelone \
ft_lstbuflen ft_lststr

FUNC_EXTRA	= \
ft_memclr

CFUNC	= $(FUNC_P12) $(FUNC_BONUS) $(FUNC_EXTRA)

SRC_DIR		= ./
OBJ_DIR		= ./
SRC			= $(addprefix $(SRC_DIR),$(addsuffix .c,$(CFUNC)))
OBJ			= $(addprefix $(OBJ_DIR),$(addsuffix .o,$(CFUNC)))
INC_DIR		= ./
LIB_DIR		=
LIB			=
FLAGS		= -Wall -Wextra -Werror -Wimplicit -Wconversion
CC			= clang

COL_HL		= \x1B[33m
COL_CS		= \x1B[32m
COL_NUL		= \x1B[0m

##	BUILD ====
all: $(NAME)
$(NAME):
	@echo -e '$(COL_HL)' '$(NAME) :: Starting build...' '$(COL_NUL)'
	$(CC) -c $(FLAGS) $(SRC) -I $(INC_DIR)
	ar -cr	$(BIN) $(OBJ)
	ranlib	$(BIN)
	@echo -e '$(COL_CS)' '$(NAME) :: Build success!' '$(COL_NUL)'
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(BIN) $(LIB)
	rm -f libft.so
re: fclean all

so:
	@echo -e '$(COL_HL)' '$(NAME) :: Starting SO build...' '$(COL_NUL)'
	$(CC) -nostartfiles -fPIC $(FLAGS) $(SRC)
	$(CC) -nostartfiles -shared -o libft.so $(OBJ)
	@echo -e '$(COL_CS)' '$(NAME) :: Build success!' '$(COL_NUL)'
