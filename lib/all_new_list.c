/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_new_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:24:30 by meserghi          #+#    #+#             */
/*   Updated: 2024/04/24 21:45:49 by meserghi         ###   ########.fr       */
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
	// t_list	*tmp;
	if (node->prv)
	{
		node->prv->next = node->next;
		node->next->is_sp = node->is_sp;
		// node->next->token = node->token;
	}
	if (node->next)
		node->next->prv = node->prv;
	// if (!node->next)
	// {
	// 	free(node->wrd);
	// 	free(node);
	// 	node = NULL;

	// }
	// else
	// {
	// 	tmp = node;

	// 	node->next = node->next->next;
	free(node->wrd);
	free(node);
	// 	node = NULL;
	// }
}