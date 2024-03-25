/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 03:41:37 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/25 22:39:31 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_if_to_wrd_empty(t_list **head)
{
	t_list	*i;
	t_list	*swap;

	i = *head;
	while (i)
	{
		if (i->next && !*i->wrd && !*i->next->wrd)
		{
			swap = i->next;
			i->next = i->next->next;
			free_node(swap);
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

t_mini	*parsing_part(char*line)
{
	t_list	*head;
	t_mini	*data;
	char	*res;

	data = NULL;
	res = ft_strtrim(line, " \t");
	if (!res)
		return (free(res), NULL);
	head = tokening(res);
	if (!head)
		return (clear_lst(&head), free(res), NULL);
	free(res);
	if (checking_syntax(&head) == -1)
		return (NULL);
	data = last_update_lst(head);
	print_t_mini(data);
	return (NULL);
}
