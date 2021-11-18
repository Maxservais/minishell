#include "../minishell.h"

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0); //remet la line a zero
		write(1, "\n", 1);
		rl_on_new_line();		//relance le prompt
		rl_redisplay();			//reaffiche la ligne precedente
		data.exit_code = 1; // doit rester 1 pour le code de sortie
	}
}

void	ft_ctrl_d(void)
{
	write(1, "exit\n", 5);
	data.exit = 1; // aucun code de sortie
}

void	sighandler_cmd(int signum)
{
	if (signum == SIGINT)
	{
		// printf("exit code =%d\n", data.exit_code);
		write(1, "\n", 1);
		rl_on_new_line();
		data.exit_code = 130; // doit devenir 130 pour le code de sortie
	}
	else if (signum == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		rl_on_new_line();
		data.exit_code = 131; // doit devenir 131 pour le code de sortie
	}
}



/*
ON GERE FORK ET PID
wait(&data->exit_code);
if (WIFSIGNALED(data->exit_code))
	data->exit_code = 128 + WTERMSIG(data->exit_code);
*/