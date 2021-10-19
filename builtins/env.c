#include "../minishell.h"

void	env(char **splited)
{
	if (!ft_strncmp(splited[0], "env", 3))
	{
		printf("TERM_PROGRAM=%s\n", getenv("TERM_PROGRAM"));
		printf("TERM=%s\n", getenv("TERM"));
		printf("SHELL=%s\n", getenv("SHELL"));
		printf("TMPDIR=%s\n", getenv("TMPDIR"));
		printf("TERM_PROGRAM_VERSION=%s\n", getenv("TERM_PROGRAM_VERSION"));
		printf("TERM_SESSION_ID=%s\n", getenv("TERM_SESSION_ID"));
		printf("ZSH=%s\n", getenv("ZSH"));
		printf("USER=%s\n", getenv("USER"));
		printf("COMMAND_MODE=%s\n", getenv("COMMAND_MODE"));
		printf("SSH_AUTH_SOCK=%s\n", getenv("SSH_AUTH_SOCK"));
		printf("__CF_USER_TEXT_ENCODING=%s\n", getenv("__CF_USER_TEXT_ENCODING"));
		printf("PAGER=%s\n", getenv("PAGER"));
		printf("LSCOLORS=%s\n", getenv("LSCOLORS"));
		printf("PATH=%s\n", getenv("PATH"));
		printf("PWD=%s\n", getenv("PWD"));
		printf("LANG=%s\n", getenv("LANG"));
		printf("ITERM_PROFILE=%s\n", getenv("ITERM_PROFILE"));
		printf("XPC_FLAGS=%s\n", getenv("XPC_FLAGS"));
		printf("XPC_SERVICE_NAME=%s\n", getenv("XPC_SERVICE_NAME"));
		printf("SHLVL=%s\n", getenv("SHLVL"));
		printf("HOME=%s\n", getenv("HOME"));
		printf("COLORFGBG=%s\n", getenv("COLORFGBG"));
		printf("LC_TERMINAL_VERSION=%s\n", getenv("LC_TERMINAL_VERSION"));
		printf("ITERM_SESSION_ID=%s\n", getenv("ITERM_SESSION_ID"));
		printf("LESS=%s\n", getenv("LESS"));
		printf("LOGNAME=%s\n", getenv("LOGNAME"));
		printf("LC_TERMINAL=%s\n", getenv("LC_TERMINAL"));
		printf("SECURITYSESSIONID=%s\n", getenv("SECURITYSESSIONID"));
		printf("COLORTERM=%s\n", getenv("COLORTERM"));
	}
}
