SRC_FILES 		=	main.c 			\
					echo.c			\
					exit.c			\
					pwd.c			\
					env.c			\
					export.c		\
					cd.c			\

OBJ_FILES		=	$(SRC_FILES:.c=.o)

NAME			=	minishell

MINISHELL_LIB	=	libminishell.a

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(MAKE) -s -C libft
	cp libft/libft.a $(MINISHELL_LIB)
	ar -rcs $(MINISHELL_LIB) $^
	$(CC) $(CFLAGS) -lreadline $(MINISHELL_LIB) -o $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ_FILES)
	$(MAKE) clean -C libft

fclean: clean
	rm -f $(NAME)
	rm -f $(MINISHELL_LIB)
	$(MAKE) fclean -C libft

re: fclean all

.PHONY: all clean fclean re
