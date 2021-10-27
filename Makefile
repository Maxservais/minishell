SRC_FILES 		=	main.c 				\
					./builtins/echo.c	\
					./builtins/exit.c	\
					./builtins/pwd.c	\
					./builtins/env.c	\
					./builtins/export.c	\
					./builtins/cd.c		\
					./builtins/unset.c	\
					./builtins/error_handler.c \
					./signals/signal.c	\
					./utils/lst.c 		\
					./execution/exec.c	\
					./pipes/pipex.c		\
					./pipes/error.c		\
					./redirections/redirection.c

OBJ_FILES		=	$(SRC_FILES:.c=.o)

NAME			=	minishell

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror -I /Users/$(USER)/.brew/opt/readline/include

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(MAKE) -s -C libft
	@cp libft/libft.a .
	@$(CC) $(CFLAGS) ${SRC_FILES} -lreadline libft.a -o $(NAME) -L /Users/$(USER)/.brew/opt/readline/lib
	@./minishell

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
