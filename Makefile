SRC_FILES 		=	main.c 					\
					./parsing/parser.c		\
					./parsing/split_pipes.c \
					./parsing/tokenizer.c	\
					./parsing/utils1.c		\
					./parsing/utils2.c		\
					./parsing/free.c		\
					./execution/builtins/echo.c		\
					./execution/builtins/exit.c		\
					./execution/builtins/pwd.c		\
					./execution/builtins/env.c		\
					./execution/builtins/export.c	\
					./execution/builtins/cd.c		\
					./execution/builtins/unset.c	\
					./execution/builtins/error_handler.c \
					./execution/exec.c				\
					./execution/pipex.c				\
					./execution/redirection.c 		\
					./signals/signal.c				\
					./utils/lst.c 					\

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
