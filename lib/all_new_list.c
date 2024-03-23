/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_new_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:24:30 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/22 22:27:07 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_mini	*create_node(char *data, char *in, char *out)
{
	t_mini	*new;

	new = malloc(sizeof(t_mini));
	if (!new)
		return (NULL);
	new->cmd = data;
	new->input = in;
	new->output = out;
	new->prv = NULL;
	new->next = NULL;
	return (new);
}

void	add_back_t_mini(t_mini **lst, t_mini *new)
{
	t_mini	*i;
	t_mini	*prv;

	if (!lst || !new)
		return ;
	i = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (i->next)
	{
		i = i->next;
		prv = i;
	}
	new->prv = prv;
	i->next = new;
}

void	cln_node(t_mini *node)
{
	int	i;

	i = -1;
	while (node->cmd[++i])
		free(node->cmd[i]);
	free(node->cmd);
	if (node->input)
		free(node->input);
	if (node->output)
		free(node->output);
	free(node);
}

void	clean_t_mini(t_mini **lst)
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
