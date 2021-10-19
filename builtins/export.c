#include "../minishell.h"

void	export(char **splited)
{
	if (!ft_strncmp(splited[0], "export", 6))
	{
		
		printf("export Apple_PubSub_Socket_Render=%s\n", getenv("Apple_PubSub_Socket_Render"));
		printf("export COLORFGBG=%s\n", getenv("COLORFGBG"));
		printf("export COLORTERM=%s\n", getenv("COLORTERM"));
		printf("export COMMAND_MODE=%s\n", getenv("COMMAND_MODE"));
		printf("export HOME=%s\n", getenv("HOME"));
		printf("export ITERM_PROFILE=%s\n", getenv("ITERM_PROFILE"));
		printf("export ITERM_SESSION_ID=%s\n", getenv("ITERM_SESSION_ID"));
		printf("export LANG=%s\n", getenv("LANG"));
		printf("export LC_TERMINAL=%s\n", getenv("LC_TERMINAL"));
		printf("export LC_TERMINAL_VERSION=%s\n", getenv("LC_TERMINAL_VERSION"));
		printf("export LESS=%s\n", getenv("LESS"));
		printf("export LOGNAME=%s\n", getenv("LOGNAME"));
		printf("export LSCOLORS=%s\n", getenv("LSCOLORS"));
		// OLPWD
		printf("export PAGER=%s\n", getenv("PAGER"));
		printf("export PATH=%s\n", getenv("PATH"));
		printf("export PWD=%s\n", getenv("PWD"));
		printf("export SECURITYSESSIONID=%s\n", getenv("SECURITYSESSIONID"));
		printf("export SHELL=%s\n", getenv("SHELL"));
		printf("export SHLVL=%s\n", getenv("SHLVL"));
		printf("export SSH_AUTH_SOCK=%s\n", getenv("SSH_AUTH_SOCK"));
		printf("export TERM=%s\n", getenv("TERM"));
		printf("export TERM_PROGRAM=%s\n", getenv("TERM_PROGRAM"));
		printf("export TERM_PROGRAM_VERSION=%s\n", getenv("TERM_PROGRAM_VERSION"));
		printf("export TERM_SESSOION_ID=%s\n", getenv("TERM_SESSOION_ID"));
		printf("export TMPDIR=%s\n", getenv("TMPDIR"));
		printf("export USER=%s\n", getenv("USER"));
		printf("export XPC_FLAGS=%s\n", getenv("XPC_FLAGS"));
		printf("export XPC_SERVICE_NAME=%s\n", getenv("XPC_SERVICE_NAME"));
		printf("export ZSH=%s\n", getenv("ZSH"));
		printf("export _=%s\n", getenv("_"));
		printf("export __CF_USER_TEXT_ENCODING=%s\n", getenv("__CF_USER_TEXT_ENCODING"));
	}
}
