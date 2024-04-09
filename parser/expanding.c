/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:19:04 by meserghi          #+#    #+#             */
/*   Updated: 2024/04/10 00:09:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_dollar_sing(char *str)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(str) - 1;
	i = 0;
	if ((len > 0 && str[len - 1] == '$') || str[len] != '$')
		return (str);
	res = malloc(len);
	if (!res)
		return (free(str), NULL);
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	remove_dollar_sign(t_list **head)
{
	t_list	*h;

	if (!head)
		return (0);
	h = *head;
	while (h->next)
	{
		if (is_q(h->next->token))
		{
			h->wrd = find_dollar_sing(h->wrd);
			if (!h->wrd)
				return (-1);
		}
		h = h->next;
	}
	return (0);
}


// int	expanding(t_list **head)
// {
// 	t_list *i;
	
// 	i = *head;
// 	if (!delete_)
// }
