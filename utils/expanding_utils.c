/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:46:48 by meserghi          #+#    #+#             */
/*   Updated: 2024/04/26 15:00:10 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_dollar(char c)
{
	if (c == '$' || c == '\'' || c == '<' || c == '>' || c == '|' || c == '\0')
		return (1);
	return (0);
}

int	is_expand(int token, int heredoc)
{
	if (token == t_word || (token == t_double_q && !heredoc))
		return (1);
	return (0);
}

int	is_var(int c)
{
	if (c == '_' || (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || \
						(c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	next_doll(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

int	len_var(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && is_var(str[i]))
		i++;
	return (i);
}
