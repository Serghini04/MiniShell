/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:20:48 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/30 03:36:16 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_empty_wrd(t_list *i)
{
	t_list	*swap;

	swap = i->next->next;
	i->wrd = ft_strjoin(i->wrd, i->next->wrd);
	if (i->next->token != t_word)
		i->token = i->next->token;
	else
		i->token = i->token;
	free_node(i->next);
	i->next = swap;
}

int	join_qoute(t_list **head)
{
	t_list	*i;

	i = *head;
	delete_if_to_wrd_empty(head);
	while (i && i->next)
	{
		if (is_q(i->token)  && i->next->wrd && !i->next->is_sp)
			join_empty_wrd(i);
		if (i && i->next && is_q(i->next->token))
		{
			if (i->token == t_word && !i->next->is_sp)
				join_empty_wrd(i);
		}
		i = i->next;
	}
	return (0);
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
			if (!is_red(i->next) && i->next->token != t_word \
													&& !is_q(i->next->token))
				return (print_error(head, i), -1);
		}
		i = i->next;
	}
	if (is_red(i) || i->token == t_pipe)
		return (print_error(head, i), -1);
	if (join_qoute(head) == -1 || split_cmd(head) == -1)
		return (clear_lst(head), -1);
	return (0);
}
