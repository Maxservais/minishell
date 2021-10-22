/* Reminders:
- Condition to check whether command is 'env' or not can be removed
once we check in the parsing which function should be called (cd, pwd, echo, etc.).
*/

#include "../minishell.h"

void	ft_exit(char **splited, int *exit)
{
	if (!ft_strncmp(splited[0], "exit", 5))
		*exit = 1;
	// if (!ft_strncmp(splited[0], "exit", 5))
	// {
	// 	if (exit_code)
	// 		exit(exit_code);
	// }
	// exit(EXIT_SUCCESS);
		
}
