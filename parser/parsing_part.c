/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 03:41:37 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/22 20:26:58 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// i wanna to clean my code and fix memory leaks ...
// start parsing like this :
/* Example For the line : cat < "Makefile" | grep something > outfile | wc -l < outfile */
//	 /---------------------------------------------------\
//   | PIPE_LINE|  CMD|      ARGS|   IN_REDIR|  OUT_REDIR|
//   |---------------------------------------------------|
//   |        00|  cat|      NULL| "Makefile"|       NULL|
//   |        01| grep| something|       NULL|    outfile|
//   |        02|   wc|        -l|    outfile|       NULL|
//   \---------------------------------------------------/
// ...

int join_qoute(t_list **head)
{
	t_list	*i;
	t_list	*swap;

	i = *head;
	while (i && i->next)
	{
		if (i->next->token == t_signle_q || i->next->token == t_double_q)
		{
			if (i->token == t_word && !i->next->is_sp)
			{
				swap = i->next->next;
				i->wrd = ft_strjoin(i->wrd, i->next->wrd);
				free_node(i->next);
				i->next = swap;
			}
		}
		if (i->token == t_signle_q || i->token == t_double_q)
		{
			if (i->next->token == t_word && !i->next->is_sp)
			{
				swap = i->next->next;
				i->wrd = ft_strjoin(i->wrd, i->next->wrd);
				free_node(i->next);
				i->next = swap;
			}
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
		if (is_red(i->token) && i->next->token != t_word \
													&& !is_q(i->next->token))
			return (print_error(head, i), -1);
		if (i->token == t_pipe)
		{
			if (!is_red(i->next->token) && i->next->token != t_word \
													&& !is_q(i->next->token))
				return (print_error(head, i), -1);
		}
		i = i->next;
	}
	if (is_red(i->token) || i->token == t_pipe)
		return (print_error(head, i), -1);
	if (join_qoute(head) == -1)
		return (clear_lst(head), 1);
	return (0);
}

t_mini	*last_update_lst(t_list **head)
{
	t_mini	*data;

	data = NULL;
}

t_mini	*parsing_part(char *line)
{
	t_list	*head;
	t_mini	*data;
	char 	*res;

	res = ft_strtrim(line, " \t");
	head = tokening(res);
	if (!head)
		return (clear_lst(&head), free(res), NULL);
	if (checking_syntax(&head) == -1)
		return (free(res), NULL);
	data = last_update_lst(head);
	print_lst(head);
	free(res);
	return (data);
}
