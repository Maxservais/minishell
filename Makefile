SRC_FILES 		=	main.c									\
					utils_main.c							\
					./parsing/create_word_tok.c				\
					./parsing/parser.c						\
					./parsing/split_pipes.c					\
					./parsing/split_pipes2.c				\
					./parsing/tokenizer.c					\
					./parsing/split_token.c					\
					./parsing/split_token2.c				\
					./parsing/utils1.c						\
					./parsing/utils2.c						\
					./parsing/utils3.c						\
					./parsing/free.c						\
					./execution/builtins/echo.c				\
					./execution/builtins/exit.c				\
					./execution/builtins/pwd.c				\
					./execution/builtins/env.c				\
					./execution/builtins/export1.c			\
					./execution/builtins/export2.c			\
					./execution/builtins/export3.c			\
					./execution/builtins/export_free.c		\
					./execution/builtins/cd.c				\
					./execution/builtins/unset.c			\
					./execution/builtins/error_handler.c	\
					./execution/error.c						\
					./execution/exec.c						\
					./execution/pipex.c						\
					./execution/redirection.c				\
					./execution/heredoc.c					\
					./execution/open_files.c				\
					./execution/utils.c						\
					./signals/signal.c						\
					./utils/lst1.c							\
					./utils/lst2.c							\

OBJ_FILES		=	$(SRC_FILES:.c=.o)

NAME			=	minishell

CC				=	gcc 

CFLAGS			=	-Wall -Wextra -Werror -I /Users/$(USER)/.brew/opt/readline/include

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(MAKE) -s -C libft
	@cp libft/libft.a .
	@$(CC) $(CFLAGS) ${SRC_FILES} -lreadline libft.a -o $(NAME) -L /Users/$(USER)/.brew/opt/readline/lib

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	@rm -f $(OBJ_FILES)
	@$(MAKE) clean -C libft
	@rm -rf *.dSYM

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C libft
	@rm -f libft.a

re: fclean all

.PHONY: all clean fclean re
