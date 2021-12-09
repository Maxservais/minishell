#include "../minishell.h"

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		data.command_code = 1; // doit rester 1 pour le code de sortie
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
		write(1, "\n", 1);
		rl_on_new_line();
		data.command_code = 2; // doit devenir 130 pour le code de sortie
	}
	else if (signum == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		rl_on_new_line();
		data.command_code = 3; // doit devenir 131 pour le code de sortie
	}
}

void	sighandler_heredoc(int signum)
{
	if (signum == SIGINT)
		exit (130);
}
