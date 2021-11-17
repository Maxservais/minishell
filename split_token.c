#include <stdio.h>

static int	check_occurence(char c, char *to_find)
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

static int	count_token(char *str, char *sep)
{
	int	counter;
	int	x;

	counter = 0;
	x = 0;
	while (str[x])
	{
		if (check_occurence(str[x], sep))
			counter++;
		x++;
	}
	return (counter);
}

int	count_words(char *str, char *sep)
{
	int counter;

	counter = 0;
	counter = count_token(str, sep);
	return (counter);
}

char	**split_token(char *str, char *sep)
{
	char **result;

	printf("%d\n", count_words(str, sep));
	return (result);
}

int	main(void)
{
	char    **result;
	int     x = 0;

	split_token("test<ok>oui>bla ", "<>()\'\"$ ");
	// result = split_token("test<ok>oui", "<>");
	// while (result[x])
	//     printf("%s\n", result[x++]);
	return (0);
}