#include "../minishell.h"

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0); //remet la line a zero
		write(1, "\n", 1);
		rl_on_new_line(); //relance le prompt
		if (data.here_doc != 1)
			rl_redisplay(); //reaffiche la ligne precedente
		data.exit_code = 1; // doit rester 1 pour le code de sortie
	}
}

void	ft_ctrl_d(void)
{
	write(1, "exit\n", 5);
	data.exit = 1;
}

void	sighandler_cmd1(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		data.exit_code = 130;
	}
}

void	sighandler_cmd(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "^C\n", 3);
		rl_on_new_line();
		data.exit_code = 130;
	}
	else if (signum == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		rl_on_new_line();
		data.exit_code = 131;
	}
}

void	sighandler_heredoc(int signum)
{
	if (signum == SIGINT)
		exit (130);
}
