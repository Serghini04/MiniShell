/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:20:48 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/31 02:59:27 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (join_qoute(head) == -1 || split_cmd(head) == -1)
		return (clear_lst(head), -1);
	return (0);
}
