/* Reminders:
- Condition to check whether command is 'env' or not can be removed
once we check in the parsing which function should be called (cd, pwd, echo, etc.).
*/

#include "../minishell.h"

void	ft_exit(t_lst *command)
{
	if (!ft_strncmp(command->content[0], "exit", 5))
	{
		command->job_done = 1;
		data.exit = 1;
	}
}
