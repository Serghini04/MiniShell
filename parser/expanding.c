/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:19:04 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/31 21:14:48 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_dollar(char *s)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{

		}
		i++;
	}
	return (NULL);
}

int	expanding(t_list **head)
{
	t_list *i;
	char	*name;

	while (i)
	{
		if (i->token == t_word || i->token == t_double_q)
		{
			name = find_dollar(i->wrd);
		}
		i = i->next;
	}
}
