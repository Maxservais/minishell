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

/* Macros */
# define READ 0
# define WRITE 1

/* Custom structs */
typedef struct s_file
{
	char	*name;
	int		fd;
	int		mode;
}				t_file;

typedef struct s_param
{
	char	***cmds;
}				t_param;

typedef struct s_lst
{
	struct s_lst	*prev;
	struct s_lst	*next;
	int				type;
	pid_t			pid; //MAYBE
	int				status;
	char			**content;
	char			**cmd;
	int				args;
	int				index;
	int				to_display;
	int				job_done;
	struct s_file	*infile;
	struct s_file	*outfile;
}				t_lst;

typedef struct s_data
{
	int				exit;
	int				new_line;
	int				nb_of_commands;
	int				command_code;
	char			**envp;
}				t_data;

typedef struct s_token
{
	int		index;
	char	token;
	int		to_ignore;
}				t_token;

/* Global variable */
t_data data;

/* Minishell */
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
char	**ft_split_pipe(char const *line, t_token *tokens);
char	**ft_test(char *s, t_token *tokens);
void	execute_builtin(t_lst *commands);

/* Built-ins */
int		pwd(t_lst *commands);
int		cd(t_lst *commands);
int		env(t_lst *commands);
int		export(t_lst *command);
int		unset(t_lst *commands);
int		ft_exit(t_lst *command);
int		echo(t_lst *commands);
void	error_cmd(char *bash, char *cmd_name, char *input);
void	error_usage(char *cmd_name, char *str, char *usage);

/* Execution */
char	**find_paths(void);
int		exec_cmd(t_lst *command);

/* Redirections */
int		ft_open(char *file_name, int mode);
int		open_files(t_lst *commands);

/* Pipes */
int		ft_err_return(char *error);
int		ft_perror(void);
int		report_error(void);
int		ft_free(char ***argv);

int		first_command(int right_pipe[], t_lst *command);
int		last_command(int left_pipe[], int right_pipe[], t_lst *command);
int		pipex(t_lst *command, int left_pipe[]);

/* Signals */
void	sighandler(int signum);
void	ft_ctrl_d(void);

#endif
