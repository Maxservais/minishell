#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
#include "libft/libft.h"

# define ECHO "echo"

/* Mini_shell */
void	export(char **splited);
void	env(char **splited);
void 	pwd(char **splited);
void	ft_exit(char **splited, int *exit);
void	echo(char **splited, int word_count);

#endif
