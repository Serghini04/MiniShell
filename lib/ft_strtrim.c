/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:07:54 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/21 02:08:04 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check(char s1, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_start(char *s1, char *set)
{
	int	i;

	i = 0;
	while (s1[i] && check(s1[i], set) == 1)
		i++;
	return (i);
}

static int	ft_end(char *s1, char *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (s1[i] && check(s1[i], set) == 1)
		i--;
	return (i);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		i;
	int		s;
	int		end;
	char	*res;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	if (*s1 == '\0')
		return (ft_strdup(s1));
	s = ft_start(s1, set);
	end = ft_end(s1, set);
	if (s > end)
		return (ft_strdup(""));
	res = malloc(end - s + 2);
	if (!res)
		return (free(s1), NULL);
	while (s + i <= end)
	{
		res[i] = s1[s + i];
		i++;
	}
	res[i] = '\0';
	free(s1);
	return (res);
}
