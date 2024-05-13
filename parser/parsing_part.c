/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 03:41:37 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/13 14:18:17 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_if_empty_wrd(t_list **head)
{
	t_list	*i;
	t_list	*tmp;

	i = *head;
	while (i && i->next)
	{
		if (is_q(i->next->token) && !*i->wrd && !i->next->is_sp)
		{
			i->next->is_sp = i->is_sp;
			if (i->prv)
				i->prv->next = i->next;
			else
				(*head) = i->next;
			if (i->next)
				i->next->prv = i->prv;
			tmp = i;
			i = i->next;
			free_node(tmp);
		}
		else
			i = i->next;
	}
}

void	add_split_lst(char **cmd, t_list **head, t_list **root)
{
	t_list	*new_head;
	t_list	*last;
	t_list	*swap;
	int		i;

	i = 0;
	new_head = NULL;
	while (cmd[i])
	{
		add_back(&new_head, new_node(ft_strdup(cmd[i]), t_word));
		i++;
	}
	last = last_lst(new_head);
	swap = (*head);
	last->next = (*head)->next;
	if ((*head)->prv)
		(*head)->prv->next = new_head;
	else
		(*root) = new_head;
	free_arr(cmd);
	(*head) = (*head)->next;
	free_node(swap);
}

t_mini	*parsing_part(char *line)
{
	t_list	*head;
	t_mini	*data;
	char	*res;

	data = NULL;
	res = ft_strtrim(line, " \t");
	if (!res)
		(free(res), exit(1));
	head = tokening(res);
	if (!head)
		return (clear_lst(&head), free(res), NULL);
	free(res);
	if (checking_syntax(&head) == -1)
		return (NULL);
	data = last_update_lst(head);
	clear_lst(&head);
	return (data);
}
