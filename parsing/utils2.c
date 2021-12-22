#include "../minishell.h"

int	last_infile(t_lst *command)
{
	int	x;

	x = 0;
	while (command->infile[x + 1].name)
		x++;
	return (x);
}

int	last_outfile(t_lst *command)
{
	int	x;

	x = 0;
	while (command->outfile[x + 1].name)
		x++;
	return (x);
}

void	add_index(t_lst **commands)
{
	int		index;
	t_lst	*trav;
	int		x;

	index = 1;
	trav = *commands;
	while (trav)
	{
		x = 0;
		trav->args = 0;
		while (trav->content[x++])
		{
			trav->args++;
		}
		trav->index = index++;
		trav = trav->next;
	}
}

int	find_equal(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	find_first_quote(char *line, int dollar)
{
	int		x;

	x = 0;
	while (line[x])
	{
		if (line[x] == '\'' && x == dollar -1)
			return (x);
		x++;
	}
	return (-1);
}

int	find_second_quote(char *line, int first_quote)
{
	while (line[first_quote])
	{
		if (line[first_quote] == '\'')
			return (first_quote);
		first_quote++;
	}
	return (-1);
}

char	*add_env(char *line, int *ret, int *count)
{
	int			x;
	int			dollar;
	int			space;
	int			quote;
	int			first_quote;
	int			last_quote;
	char		*key;
	char		*string_before;
	char		*string_after;
	char		*sub_str;
	char		*value;
	char		*temp;
	char		*new_line;

	x = 0;
	value = NULL;
	dollar = char_position(line, '$', *ret);
	// printf("dollar index:%d\n", dollar);
	space = space_position(line, ' ', dollar);
	quote = space_position(line, '\"', dollar);
	if (quote < space)
		space = quote;
	first_quote = find_first_quote(line, dollar); // Remodifier
	last_quote = find_second_quote(line, first_quote); // Remodifier
	if (first_quote > -1 && last_quote > -1 && first_quote < dollar && last_quote < space)
	{
		// free les bons trucs
		*ret += 1;
		*count = nbr_of_dollars(line);
		return (line);
	}
	if (dollar >= 0)
	{
		key = ft_substr(line, dollar + 1, space - dollar - 1);
		// printf("key:|%s|\n", key);
		string_before = ft_substr(line, 0, dollar);
		string_after = ft_substr(line, space, ft_strlen(line) - space);
		// printf("before:%s\n", string_before);
		// printf("after:%s\n", string_after);
		if (key[0] == '?')
			value = ft_itoa(data.exit_code);
		while (!value && data.envp[x])
		{
			sub_str = ft_substr(data.envp[x], 0, find_equal(data.envp[x]));
			if (!ft_strcmp_parse(sub_str, key, ft_strlen(sub_str)))
			{
				value = ft_substr(data.envp[x], ft_strlen(key) + 1, ft_strlen(data.envp[x]) - 1 - ft_strlen(key));
				free (sub_str);
				break ;
			}
			free(sub_str);
			sub_str = NULL;
			x++;
		}
		if (!value)
		{
			temp = ft_strjoin(string_before, string_after);
			free(key);
			free(string_before);
			free(string_after);
			// *ret += 1;
			*count = nbr_of_dollars(temp);
			return (temp);
		}
		temp = ft_strjoin(string_before, value);
		// printf("tmp:|%s|\n", temp);
		free(value);
		free(string_before);
		new_line = ft_strjoin(temp, string_after);
		// printf("new_line:|%s|\n", new_line);
		free(string_after);
		free(temp);
		free(key);
		// *ret += 1;
		*count = nbr_of_dollars(new_line);
		return (new_line);
	}
	// *ret += 1;
	*count = nbr_of_dollars(line);
	return (line);
	// printf("value:%s\n", value);
}
