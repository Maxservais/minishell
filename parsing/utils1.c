#include "../minishell.h"

int	check_occurence(char c, char *to_find)
{
	int	x;

	x = 0;
	while (to_find[x])
	{
		if (to_find[x] == c)
			return (1);
		x++;
	}
	return (0);
}

int	space_position(char *line, char c, int start)
{
	int	position;

	position = start;
	while (line[position])
	{
		if (line[position] == c)
			return (position);
		position++;
		if (!line[position])
			return (position);
	}
	return (-1);
}

int	char_position(char *line, char c)
{
	int	position;

	position = 0;
	while (line[position])
	{
		if (line[position] == c)
			return (position);
		position++;
	}
	return (-1);

}

int	count_chevrons(t_lst command, char chevron)
{
	int	x;
	int	counter;

	x = 0;	
	counter = 0;
	while (command.content[x])
	{
		if (command.content[x][0] == chevron)
			counter++;
		x++;
	}
	return (counter);
}
