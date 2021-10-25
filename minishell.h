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
# include <signal.h>
# include "libft/libft.h"
# include <termios.h>

typedef struct s_data
{
	int	exit;
	int	new_line;
	int	nb_of_commands;
	int	command_code;
}				t_data;

t_data data;

typedef struct s_lst
{
	struct s_lst	*prev;
	int				type;
	char			**content;
	int				index;
	int				to_display;
	int				job_done;
	struct s_lst	*next;
}				t_lst;


/* Mini_shell */
char	**handle_dquote(char *line, char **commands, int *quote);
char	**quote_remover(char **commands, char first_quote);
int		count_occurence(char *str, char c);
int		occ_in_commands(char **commands, char c);
char	*ft_strnljoin(char const *s1, char const *s2);
int     lstsize(t_lst *lst);
void	lstdelone(t_lst *lst);
void	lstclear(t_lst **lst);
void	lstadd_back(t_lst **lst, t_lst *new);
t_lst	*lstnew(char **content, int index);
t_lst	*lstlast(t_lst *lst);
char	*dquote(char *line);
char	find_first_quote(char *line);
char	*remove_useless_quotes(char *line, char first_quote);

/* Built-ins */
int		pwd(t_lst *commands);
int		cd(t_lst *commands);
int		env(t_lst *commands);
int		export(t_lst *command);
void	ft_exit(t_lst *command);
void	echo(t_lst *commands);

#endif
