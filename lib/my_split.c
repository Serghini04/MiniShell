/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:33:07 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/21 10:35:21 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_word(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] && !ft_isspace(str[i]))
			count++;
		while (str[i] && !ft_isspace(str[i]))
			i++;
	}
	return (count);
}

static char	*get_word(char *s)
{
	char	*res;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (s[len] && !ft_isspace(s[len]))
		len++;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (s[i] && !ft_isspace(s[i]))
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static void	free_split(char **res, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(res[i]);
		i++;
	}
	free(res);
}

static char	**split_string(char const *s, int word_count)
{
	char	**res;
	int		i;

	i = 0;
	(void)word_count;
	res = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (*s && !ft_isspace(*s))
		{
			res[i] = get_word((char *)s);
			if (!res[i])
				return (free_split(res, i), NULL);
			i++;
		}
		while (*s && !ft_isspace(*s))
			s++;
	}
	res[i] = 0;
	return (res);
}

char	**my_split(char const *s)
{
	int	word_count;

	if (!s)
		return (NULL);
	word_count = count_word((char *)s);
	return (split_string(s, word_count));
}
