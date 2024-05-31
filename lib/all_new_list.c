/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_new_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:24:30 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/28 12:12:55 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_mini	*create_node(void)
{
	t_mini	*new;

	new = malloc(sizeof(t_mini));
	if (!new)
		return (NULL);
	new->fd_in = 0;
	new->fd_out = 1;
	new->next = NULL;
	return (new);
}

void	add_back_t_mini(t_mini **lst, t_mini *new)
{
	t_mini	*i;

	if (!lst || !new)
		return ;
	i = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (i->next)
		i = i->next;
	i->next = new;
}

void	cln_node(t_mini *node)
{
	int	i;

	i = -1;
	while (node->cmd[++i])
		free(node->cmd[i]);
	free(node->cmd);
	if (node->fd_in != -1 && node->fd_in != 0)
		close(node->fd_in);
	if (node->fd_out != -1 && node->fd_out != 1)
		close(node->fd_out);
	free(node);
}

void	clear_t_mini(t_mini **lst)
{
	t_mini	*i;
	t_mini	*swap;

	if (!lst)
		return ;
	i = *lst;
	while (i)
	{
		swap = i->next;
		cln_node(i);
		i = swap;
	}
	*lst = NULL;
}

void	delete_node(t_list *node)
{
	if (node->prv)
		node->prv->next = node->next;
	if (node->next)
	{
		node->next->prv = node->prv;
		if (!node->is_sp && !node->next->is_sp)
			node->next->is_sp = 0;
		else
			node->next->is_sp = 1;
	}
	free(node->wrd);
	free(node);
}
