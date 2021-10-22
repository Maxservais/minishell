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
# include <errno.h>
# include <string.h>
#include "libft/libft.h"

/* Minishell */
char	**handle_dquote(char *line, char **commands);
char	**quote_remover(char **commands);
int		count_occurence(char *str, char c);
int		occ_in_commands(char **commands, char c);

/* Built-ins */
int		pwd(char **splited);
int		cd(char **splited);
int		env(char **splited);
void	export(char **splited);
void	ft_exit(char **splited, int *exit);
void	echo(char **splited, int word_count, int quote);

#endif
