/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 03:41:37 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/31 11:14:48 by meserghi         ###   ########.fr       */
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
	t_list	*node;
	t_list	*last;
	t_list	*swap;
	int		i;

	(1) && (i = 0, new_head = NULL);
	while (cmd[i])
	{
		node = new_node(ft_strdup(cmd[i]), t_word);
		if (!i)
			node->is_sp = (*head)->is_sp;
		add_back(&new_head, node);
		i++;
	}
	last = last_lst(new_head);
	(1) && (swap = (*head), last->next = (*head)->next);
	((*head)->next) && ((*head)->next->prv = last);
	if ((*head)->prv)
		(*head)->prv->next = new_head;
	else
		(*root) = new_head;
	(*head) = (*head)->next;
	(free_arr(cmd), free_node(swap));
}

t_mini	*parsing_part(char *line)
{
	t_list	*head;
	t_mini	*data;
	char	*res;

	data = NULL;
	res = ft_strtrim(line, " \t");
	if (!res)
		return (free(line), NULL);
	head = tokening(res);
	free(res);
	if (!head)
		return (NULL);
	if (checking_syntax(&head) == -1)
		return (NULL);
	data = last_update_lst(head);
	clear_lst(&head);
	return (data);
}

t_mini	*last_update_node(int *fd, t_mini **node, int *index)
{
	extern int	g_sig_global;

	g_sig_global = 0;
	(*node)->cmd[*index] = NULL;
	if (dup2(*fd, 0) == -1)
	{
		close(*fd);
		free_arr((*node)->cmd);
		free(*node);
		return (NULL);
	}
	close(*fd);
	return (*node);
}
