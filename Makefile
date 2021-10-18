# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xauffray <xauffray@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/28 11:47:14 by mservais          #+#    #+#              #
#    Updated: 2021/10/18 23:29:52 by xauffray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FILES		=	pipex.c \
					error.c \
					utils.c

OBJ_FILES		=	$(SRC_FILES:.c=.o)

NAME			=	pipex

PIPEX_LIB		=	libpipex.a

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror


all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(MAKE) -s -C libft
	cp libft/libft.a $(PIPEX_LIB)
	ar -rcs $(PIPEX_LIB) $^
	$(CC) $(CFLAGS) $(PIPEX_LIB) -o $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ_FILES) $(OBJ_FILES_BONUS)
	$(MAKE) clean -C libft

shell:
	@gcc main.c -lreadline libft/libft.a && ./a.out


fclean: clean
	rm -f $(NAME)
	rm -f $(PIPEX_LIB)
	$(MAKE) fclean -C libft

re: fclean all

.PHONY: all clean fclean re
