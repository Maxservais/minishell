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
# include <signal.h>
# include <errno.h>
# include <string.h>
# include "libft/libft.h"

# define ECHO "echo"

typedef struct s_data
{
    int     exit;
    int     new_line;
}		    	t_data;

t_data data;

typedef struct s_lst
{
    struct s_lst   *prev;
    int             type;
	char			**content;
	struct s_lst	*next;
}				t_lst;


/* Mini_shell */
void	export(char **splited);
void	env(char **splited);
void 	pwd(char **splited);
void	ft_exit(t_lst command);
void	echo(t_lst commands);
char	**handle_dquote(char *line, char **commands, int *quote);
char	**quote_remover(char **commands, char first_quote);
int		count_occurence(char *str, char c);
int		occ_in_commands(char **commands, char c);
char	*ft_strnljoin(char const *s1, char const *s2);
int     lstsize(t_lst *lst);
void	lstdelone(t_lst *lst);
void	lstclear(t_lst **lst);
void	lstadd_back(t_lst **lst, t_lst *new);
t_lst	*lstnew(char **content);
t_lst	*lstlast(t_lst *lst);
void	sighandler(int signum);

/* Built-ins */
void	pwd(char **splited);
void	cd(char **splited);
void	ft_ctrl_d();
void	sighandler(int signum);

#endif
