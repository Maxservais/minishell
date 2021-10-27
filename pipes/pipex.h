#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_param
{
	char	***cmds;
}				t_param;

/* Error handling */
int		ft_err_return(char *error);
int		ft_perror(void);
int		report_error(void);
int		ft_free(char ***argv);

#endif
