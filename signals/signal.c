#include "../minishell.h"

void	sighandler(int signum)
{
	if (signum == 2)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_ctrl_d(void)
{
	write(1, "exit\n", 5);
	data.exit = 1;
}
