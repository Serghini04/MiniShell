/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:54:31 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/20 14:58:04 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_name_wildcard(char *line, int i )
{
	int	pos;

	pos = i + 1;
	while (i > 0 && line[i] != '*')
		i--;
	if (i > 0 && line[i] == '*')
		i++;
	return (ft_substr(line, i, pos - i));
}

char	*get_name_part2(char *line, int *i)
{
	int	s;

	s = *i;
	while (line[*i] && line[*i] != '*')
		(*i)++;
	return (ft_substr(line, s, *i - s));
}

int	reverse_cmp(char *s1, char *s2, int len)
{
	int	i;
	int	j;

	i = strlen(s1) - 1;
	j = strlen(s2) - 1;
	while (i >= 0 && j >= 0 && s1[i] == s2[j] && len > 0)
	{
		i--;
		j--;
		len--;
	}
	return (len);
}
