#include "../minishell.h"

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0); //remet la line a zero
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line(); //relance le prompt
		if (g_data.here_doc != 1)
			rl_redisplay(); //reaffiche la ligne precedente
		g_data.exit_code = 1; // doit rester 1 pour le code de sortie
	}
}

void	ft_ctrl_d(void)
{
	write(STDOUT_FILENO, "exit\n", 5);
	g_data.exit = 1;
}

void	sighandler_cmd1(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		g_data.exit_code = 130;
	}
}

void	sighandler_cmd(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "^C\n", 3);
		rl_on_new_line();
		g_data.exit_code = 130;
	}
	else if (signum == SIGQUIT)
	{
		write(STDOUT_FILENO, "^\\Quit: 3\n", 10);
		rl_on_new_line();
		g_data.exit_code = 131;
	}
}

void	sighandler_heredoc(int signum)
{
	if (signum == SIGINT)
		exit (1);
}
