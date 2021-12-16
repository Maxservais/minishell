#ifndef MINISHELL_H
# define MINISHELL_H

/* 0. EXTERNAL LIBRARIES */

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

/* 1. MACROS */

# define READ 0
# define WRITE 1
# define NO_SUCH_FILE ": No such file or directory\n"
# define INVALID_COMMAND ": command not found\n"

/* 2. CUSTOM STRUCTS */

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
	pid_t			pid;
	int				status;
	int				save_stdin;
	int				save_stdout;
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
	int				exit_code;
	int				built;
	int				here_doc;
	char			**envp;
	struct termios	main_old;
	struct termios	main_new;
}				t_data;

typedef struct s_token
{
	int		index;
	char	token;
	int		to_ignore;
}				t_token;

typedef struct s_operations
{
	char	*operation;
	int		size;
}				t_operation;

/* 3. GLOBAL VARIABLE */

t_data	data; // IS it norminette compliant???? NO, c'est une global il faut la declarer autrement

/* 4. MAIN FUNCTIONS */

void	parser_test(char *line);
void	prompt_test(char *line);

/* 5. PARSER */

/* 5.0 Parser */
t_lst	*put_in_list(char **splited);
void	remove_files(t_lst **commands);
char	**ft_test(char *s, t_token *tokens);

/* 5.1 Tokenizer */
t_token	*token_finder(char *line);
char	**split_token(char *str);

/* 5.2 Utils */
int		check_occurence(char c, char *to_find);
int		space_position(char *line, char c, int start);
int		char_position(char *line, char c);
int		count_chevrons(t_lst command, char *chevron);
int		last_infile(t_lst *command);
int		last_outfile(t_lst *command);
void	add_index(t_lst **commands);
char	*add_env(char *line);
int		strisdigit(char *str);
int		ft_strcmp(char *str, char *end);
int		ft_strcmp_unset(char *str, char *end);

/* 5.3 Free Memory */
void	free_splited(char **splited);
void	clean_all(t_token *tokens, char **splited, t_lst **commands);
void	free_envp(void);

/* 6. EXECUTOR */

/* 6.0 Builtins */
int		pwd(t_lst *commands);
int		cd(t_lst *commands);
int		copy_env(void);
int		env(t_lst *commands);
int		export(t_lst *command);
int		unset(t_lst *commands);
int		ft_exit(t_lst *command);
int		echo(t_lst *commands);
void	error_cmd(char *bash, char *cmd_name, char *input);
void	error_usage(char *cmd_name, char *str, char *usage);

/* 6.1 Execution */
void	handle_command(t_lst *commands);
int		handle_one_command(t_lst *commands);
void	execute_builtin(t_lst *commands);
void	test_built(t_lst *commands);

/* 6.2 Piping */
int		first_command(int right_pipe[], t_lst *command);
int		last_command(int left_pipe[], int right_pipe[], t_lst *command);
int		inter_command(int l_pipe[], int r_pipe[], t_lst *command);
int		pipex(t_lst *command, int left_pipe[]);

/* 6.3 Redirections */
void	add_files(t_lst *commands);
int		ft_open(char *file_name, int mode);
int		open_files(t_lst *commands);
int		close_files(t_lst *commands);
int		last_heredoc(t_lst *command);
int		redirect_files(t_lst *commands);
int		redirect_standard(t_lst *commands);
int		heredoc(t_lst *commands, int index);

/* 6.4 Utils */
char	**find_paths(void);
void	exec_cmd(t_lst *command);

/* 7. SIGNALS */
void	sighandler(int signum);
void	ft_ctrl_d(void);
void	sighandler_cmd(int signum);
void	sighandler_cmd1(int signum);
void	sighandler_heredoc(int signum);

/* 8. LIST MANIPULATION */
int		lstsize(t_lst *lst);
t_lst	*lstnew(char **content, int index);
void	lstdelone(t_lst *lst);
void	lstclear(t_lst **lst);
void	lstadd_back(t_lst **lst, t_lst *new);
int		ft_strcmp(char *str, char *end);

/* 9. ERROR HANDLING */
void	command_not_found(t_lst *commands);
void	invalid_file(t_lst *commands, int i);
void	invalid_path(t_lst *commands);

#endif
