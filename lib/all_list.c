/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:47:40 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/28 12:11:52 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*new_node(char *data, int token)
{
	t_list	*new;

	if (!data)
		return (NULL);
	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->wrd = data;
	new->token = token;
	new->is_sp = 1;
	if (token != t_word)
		new->exp_wildcard = 0;
	else
		new->exp_wildcard = 1;
	new->prv = NULL;
	new->next = NULL;
	return (new);
}

void	add_back(t_list **lst, t_list *new)
{
	t_list	*i;

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
	new->prv = i;
	i->next = new;
}

void	free_node(t_list *node)
{
	if (!node)
		return ;
	free(node->wrd);
	free(node);
}

void	clear_lst(t_list **lst)
{
	t_list	*i;
	t_list	*swap;

	if (!lst)
		return ;
	i = *lst;
	while (i)
	{
		swap = i->next;
		free_node(i);
		i = swap;
	}
	*lst = NULL;
}

t_list	*last_lst(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
