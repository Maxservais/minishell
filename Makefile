SRC_FILES 		=	main.c 			\
					./builtins/echo.c	\
					./builtins/exit.c	\
					./builtins/pwd.c		\
					./builtins/env.c		\
					./builtins/export.c	\
					./builtins/cd.c		\

OBJ_FILES		=	$(SRC_FILES:.c=.o)

NAME			=	minishell

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(MAKE) -s -C libft
	@cp libft/libft.a .
	@$(CC) $(CFLAGS) ${SRC_FILES} -lreadline libft.a -o $(NAME)
	@./$(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	@rm -f $(OBJ_FILES)
	@$(MAKE) clean -C libft

fclean: clean
	@rm -f $(NAME)
	@rm -f $(MINISHELL_LIB)
	@$(MAKE) fclean -C libft
	@rm -f libft.a

re: fclean all

.PHONY: all clean fclean re
