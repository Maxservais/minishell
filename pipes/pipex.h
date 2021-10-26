#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include "./libft/libft.h"

# define READ 0
# define WRITE 1

typedef struct s_param
{
	int		fd1;
	int		fd2;
	int		pos;
	pid_t	pid;
	int		status;
	char	***cmds;
}				t_param;

/* Pipex program */
int		first_command(char **envp, int right_pipe[], t_param *param);
int		last_command(char **envp, int l_pipe[], int r_pipe[], t_param *p);
int		inter_command(char **envp, int l_pipe[], int r_pipe[], t_param *p);
int		pipex(char **envp, t_param *param, int left_pipe[]);
int		main(int argc, char **argv, char **envp);

/* Error handling */
int		ft_err_return(char *error);
int		ft_perror(void);
int		report_error(void);
int		ft_free(char ***argv);

#endif
