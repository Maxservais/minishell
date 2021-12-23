#include "../minishell.h"

int	check_for_quote(t_check_quote arg)
{
	while (*(arg.str + *arg.i) && !check_occ_tok(arg.str + (*arg.i)++, arg.o))
		arg.len++;
	*arg.i = 0;
	if (*(arg.str + *arg.i) == arg.frstquote)
	{
		(*arg.i)++;
		while (*(arg.str + *arg.i) != arg.frstquote)
		{
			(*arg.i)++;
			arg.len++;
		}
		(*arg.i)++;
	}
	return (arg.len);
}

void	ft_str_word(char *word, int *i, char *str, int *len)
{
	word[*i] = (str)[*i];
	(*i)++;
	(*len)--;
}

void	copy_word(t_copy_word arg)
{
	*arg.i = 0;
	while (arg.len--)
	{
		if (*arg.str == arg.frstquote)
			arg.word[*arg.i] = (arg.str)[(*arg.i) + 1];
		else
			arg.word[*arg.i] = (arg.str)[(*arg.i)];
		(*arg.i)++;
	}
	arg.word[*arg.i] = '\0';
	if (*arg.str == arg.frstquote)
		(*arg.i) += 2;
}
