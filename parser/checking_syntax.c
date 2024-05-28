/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:20:48 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/26 15:23:30 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_dollar_sing(char *str)
{
	char	*res;
	int		len;
	int		i;

	if (!str || !*str)
		return (str);
	len = ft_strlen(str) - 1;
	i = 0;
	if ((len > 0 && str[len - 1] == '$') || str[len] != '$')
		return (str);
	res = malloc(len + 1);
	if (!res)
		return (free(str), NULL);
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (free(str), res);
}

int	remove_dollar_sign(t_list **head)
{
	t_list	*h;

	if (!head)
		return (0);
	h = *head;
	if (!*head)
		return (-1);
	while (h->next)
	{
		if (is_q(h->next->token) && h->token == t_word)
		{
			h->wrd = find_dollar_sing(h->wrd);
			if (!h->wrd)
				return (-1);
		}
		h = h->next;
	}
	return (expanding(head));
}

int	checking_syntax(t_list **head)
{
	t_list	*i;

	i = *head;
	if (i->token == t_pipe)
		return (print_error(head, i), -1);
	while (i->next)
	{
		if (is_red(i) && i->next->token != t_word \
													&& !is_q(i->next->token))
			return (print_error(head, i), -1);
		if (i->token == t_pipe)
		{
			if (i->next && !is_red(i->next) && i->next->token != t_word \
													&& !is_q(i->next->token))
				return (print_error(head, i), -1);
		}
		i = i->next;
	}
	if (i && (is_red(i) || i->token == t_pipe))
		return (print_error(head, i), -1);
	if (remove_dollar_sign(head) == -1 || join_qoute(head) == -1 || \
										split_cmd(head) == -1)
		return (clear_lst(head), -1);
	return (wildcards_part(head));
}
