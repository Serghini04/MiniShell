/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:47:40 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/23 22:47:06 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*new_node(char *data, int token)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->wrd = data;
	new->token = token;
	new->is_sp = 1;
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

void	print_lst(t_list *h)
{
	t_list	*i;

	i = h;
	printf("---------------------------------\n");
	while (i)
	{
		printf(">>%s<< ===> %d ==> %d\n", i->wrd, i->token, i->is_sp);
		i = i->next;
	}
	printf("\n---------------------------------\n");
}
