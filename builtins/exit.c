/* Reminders:
- Condition to check whether command is 'env' or not can be removed
once we check in the parsing which function should be called (cd, pwd, echo, etc.).
*/

#include "../minishell.h"

int	ft_exit(t_lst *commands)
{
	data.exit = 1;
	commands->job_done = 1;
	return (0);
}
