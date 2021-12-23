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
# include <termios.h>
# include "libft/libft.h"

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

typedef struct s_dollar
{
	int		x;
	int		dollar;
	int		space;
	int		quote;
	int		first_quote;
	int		last_quote;
	char	*key;
	char	*string_before;
	char	*string_after;
	char	*sub_str;
	char	*value;
	char	*temp;
	char	*new_line;
}				t_dollar;

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
	struct s_file	*infile;
	struct s_file	*outfile;
}				t_lst;

typedef struct s_data
{
	int				exit;
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

typedef struct s_check_quote
{
	int			*i;
	char		*str;
	t_operation	*o;
	char		frstquote;
	int			len;
}				t_check_quote;

typedef struct s_copy_word
{
	int			*i;
	char		*str;
	char		frstquote;
	char		*word;
	int			len;
}				t_copy_word;

typedef struct s_count_token
{
	int			*counter;
	char		**str;
	t_operation	*o;
	char		first_quote;
}				t_count_token;

typedef struct s_append_char
{
	char	*key;
	char	*value;
	char	*to_append;
	char	*tmp1;
	char	*tmp2;
	char	*final;
	char	c;
}				t_append_char;

typedef struct s_exported
{
	int		i;
	int		plus;
	int		equal;
	char	*key_str;
	char	*key_envp;
	char	*tmp;
}				t_exported;

typedef struct s_add_to_envp
{
	int		i;
	int		plus;
	char	*key;
	char	*value;
	char	*tmp;
	char	**new_envp;
}				t_add_to_envp;

typedef struct s_find_var_unset
{
	int		i;
	int		plus;
	int		equal;
	int		ok;
	char	*key_str;
	char	*key_envp;
	char	*tmp;
}				t_find_var_unset;

/* 3. GLOBAL VARIABLE */

t_data	g_data;

/* 4. MAIN FUNCTIONS */

char	*line_env(char *line);
void	parser_test(char *line);
char	*ft_space_line(char *line);
void	prompt_test(char *line);
int		is_error(char *line);
int		nbr_of_dollars(char *line);
void	rem_handcom_clean(t_lst *commands, t_token *tokens, char **splited);

/* 5. PARSER */

/* 5.0 Parser */
t_lst	*put_in_list(char **splited);
int		syntax_error(void);
int		check_syntax(t_lst *commands);
int		check_chevron(t_lst *comd, int x, int y);
void	remove_files(t_lst *commands);
char	**ft_test(char *s, t_token *tokens);
int		in_quotes(t_token *tokens, int pos);

/* 5.1 Tokenizer */
int		check_occ_tok(char *str, t_operation *o);
char	find_first_quote_tok(char *str);
void	fill(char **result, char *str, t_operation *o, int size);
void	count_w_token(t_count_token arg);
int		count_words_tok(char *str, t_operation *o);
void	assignation_o(t_operation *o);
char	**split_token(char *str);
int		check_for_quote(t_check_quote arg);
void	ft_str_word(char *word, int *i, char *str, int *len);
void	copy_word(t_copy_word arg);
t_token	*token_finder(char *line);

/* 5.2 Utils */
int		check_occurence(char c, char *to_find);
int		space_position(char *line, char c, int start);
int		char_position(char *line, char c, int occ);
int		count_chev(t_lst command, char *chevron);
void	add_index(t_lst **commands);
int		last_infile(t_lst *command);
int		last_outfile(t_lst *command);
int		find_equal(char *line);
int		find_f_quote(char *line, int dollar);
int		find_sec_quote(char *line, int first_quote);
void	init_value(t_dollar *dollar, char *line, int *ret);
void	remove_dollar1(t_dollar *d, char *line);
char	*remove_dollar2(t_dollar *d, int *count);
char	*add_env(char *line, int *ret, int *count);

/* 5.3 Memory management */
void	free_splited(char **splited);
void	clean_all(t_token *tokens, char **splited, t_lst **commands);
void	free_envp(void);

/* 6. EXECUTOR */

/* 6.0 Builtins */
int		cd(t_lst *commands);
int		echo(t_lst *command);
int		copy_env(void);
int		env(t_lst *commands);
int		ft_exit(t_lst *commands);
int		pwd(t_lst *commands);
int		unset(t_lst *commands);
char	*append_char(char *str, char *str_before);
int		export(t_lst *commands);
int		find_equal_c(char *str);
int		ft_find_plus(char *str);
int		len_env(char **env);
int		exported(char *str);
int		add_to_envp(char *str);
void	exported_ok(t_lst *commands, int i);
void	free_exported(t_exported vars, char *str);
void	join_free(t_add_to_envp var, char *str);
int		free_new_envp(t_add_to_envp var);
void	error_cmd(char *bash, char *cmd_name, char *input);
void	error_usage(char *cmd_name, char *str, char *usage);

/* 6.1 Execution */
void	handle_command(t_lst *commands);
int		execute_one_command(t_lst *commands);
int		handle_one_command(t_lst *commands);
void	test_built(t_lst *commands);
void	execute_builtin(t_lst *commands);

/* 6.2 Piping */
int		first_command(int right_pipe[], t_lst *command);
int		last_command(int left_pipe[], int right_pipe[], t_lst *command);
int		inter_command(int l_pipe[], int r_pipe[], t_lst *command, int err);
int		pipex(t_lst *command, int left_pipe[]);

/* 6.3 Redirections */
void	add_files_loop(t_lst *commands, int *x, int *y, int *z);
int		add_files(t_lst *commands);
int		redirect_input(int index, t_lst *commands);
int		redirect_files(t_lst *commands);
int		redirect_standard(t_lst *commands);
int		ft_open(char *file_name, int mode);
int		open_files(t_lst *commands);
int		close_files(t_lst *commands);
int		last_heredoc(t_lst *command);
int		heredoc_bis(int x, t_lst *commands, char *str, int fd);
int		heredoc(t_lst *commands, int index);

/* 6.4 Utils */
char	**find_paths(void);
void	exec_cmd(t_lst *command, int i);

/* 6.5 Error handling */
void	command_not_found(t_lst *commands);
int		invalid_file(t_lst *commands, int i);
void	invalid_path(t_lst *commands);
int		pipe_error(void);

/* 7. SIGNALS */
void	sighandler(int signum);
void	ft_ctrl_d(void);
void	sighandler_cmd(int signum);
void	sighandler_cmd1(int signum);
void	sighandler_heredoc(int signum);

/* 8. UTILS */
int		lstsize(t_lst *lst);
t_lst	*lstnew(char **content, int index);
t_lst	*lstlast(t_lst *lst);
void	lstadd_back(t_lst **lst, t_lst *new);
void	lstclear(t_lst **lst);
void	lstdelone(t_lst *lst);
int		ft_strisdigit(char *str);
int		ft_strcmp(char *str, char *end);
int		ft_strcmp_unset(char *str, char *end);
int		ft_strcmp_parse(char *str1, char *str2, int n);

#endif
