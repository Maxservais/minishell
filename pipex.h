/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xauffray <xauffray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 10:57:37 by mservais          #+#    #+#             */
/*   Updated: 2021/10/19 11:52:00 by xauffray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include "./libft/libft.h"

# define ERROR_USAGE "Usage: ./pipex infile cmd1 cmd2 outfile\n"
# define READ 0
# define WRITE 1
# define ECHO "echo"

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

/* Utils */
int		open_file(char *file_name, int mode);
char	**find_paths(char **envp);
int		exec_cmd(char **cmd, char **envp);

/* Error handling */
int		ft_err_return(char *error);
int		ft_perror(void);
int		report_error(void);
int		ft_free(char ***argv);

/* Mini_shell */
void	export(char **splited);
void	env(char **splited);
void 	pwd(char **splited);
void	ft_exit(char **splited, int *exit);
void	echo(char **splited, int word_count);

#endif
