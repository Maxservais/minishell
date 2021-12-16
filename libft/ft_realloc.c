#include "libft.h"

char	*ft_realloc(char *str, int to_add)
{
	char	*new;
	int		len;

	len = -1;
	if (str)
		while (str[++len])
			;
	new = malloc(sizeof(char) * (len + to_add));
	if (!new)
		return (NULL);
	if (new)
	{
		len = -1;
		if (str)
			while (str[++len])
				new[len] = str[len];
		new[len] = 0;
	}
	free(str);
	str = NULL;
	return (new);
}
