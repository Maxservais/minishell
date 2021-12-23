#include "../minishell.h"

void	init_value(t_dollar *dollar, char *line, int *ret)
{
	dollar->x = 0;
	dollar->value = NULL;
	dollar->dollar = char_position(line, '$', *ret);
	dollar->space = space_position(line, ' ', dollar->dollar);
	dollar->quote = space_position(line, '\"', dollar->dollar);
	if (dollar->quote < dollar->space)
		dollar->space = dollar->quote;
	dollar->first_quote = find_f_quote(line, dollar->dollar);
	dollar->last_quote = find_sec_quote(line, dollar->first_quote + 1);
}

void	remove_dollar1(t_dollar *d, char *line)
{
	d->key = ft_substr(line, d->dollar + 1, d->space - d->dollar - 1);
	d->string_before = ft_substr(line, 0, d->dollar);
	d->string_after = ft_substr(line, d->space, ft_strlen(line) - d->space);
	if (d->key[0] == '?')
		d->value = ft_itoa(g_data.exit_code);
	while (!d->value && g_data.envp[d->x])
	{
		d->sub_str = ft_substr(g_data.envp[d->x], 0,
				find_equal(g_data.envp[d->x]));
		if (!ft_strcmp_parse(d->sub_str, d->key, ft_strlen(d->sub_str)))
		{
			d->value = ft_substr(g_data.envp[d->x], ft_strlen(d->key) + 1,
					ft_strlen(g_data.envp[d->x]) - 1 - ft_strlen(d->key));
			free (d->sub_str);
			break ;
		}
		free(d->sub_str);
		d->sub_str = NULL;
		d->x++;
	}
}

char	*remove_dollar2(t_dollar *d, int *count)
{
	if (!d->value)
	{
		d->temp = ft_strjoin(d->string_before, d->string_after);
		free(d->key);
		free(d->string_before);
		free(d->string_after);
		*count = nbr_of_dollars(d->temp);
		return (d->temp);
	}
	else
	{
		d->temp = ft_strjoin(d->string_before, d->value);
		free(d->value);
		free(d->string_before);
		d->new_line = ft_strjoin(d->temp, d->string_after);
		free(d->string_after);
		free(d->temp);
		free(d->key);
		*count = nbr_of_dollars(d->new_line);
		return (d->new_line);
	}
}

char	*add_env(char *line, int *ret, int *count)
{
	t_dollar	dollar;

	init_value(&dollar, line, ret);
	if (dollar.first_quote > -1 && dollar.last_quote > -1 && dollar.first_quote
		< dollar.dollar && dollar.last_quote < dollar.space)
	{
		*ret += 1;
		*count = nbr_of_dollars(line);
		dollar.temp = ft_strdup(line);
		return (dollar.temp);
	}
	else if (dollar.dollar >= 0)
	{
		remove_dollar1(&dollar, line);
		return (remove_dollar2(&dollar, count));
	}
	else
	{
		*count = nbr_of_dollars(line);
		return (line);
	}
}
