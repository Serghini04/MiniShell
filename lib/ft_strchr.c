
#include "../minishell.h"

char	*ft_strchr(char *s, int c)
{
    int i;

    i = 0;
    if (!s)
        return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (0);
}
