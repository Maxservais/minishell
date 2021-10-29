#include "../minishell.h"

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		data.command_code = 130;
	}
}

void	ft_ctrl_d(void)
{
	write(1, "exit\n", 5);
	data.exit = 1;
}

void	sighandler_cmd(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
	else if (signum == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		rl_on_new_line();
	}
}
