/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:47:40 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/20 02:20:31 by meserghi         ###   ########.fr       */
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
	new->next = NULL;
	new->prv = NULL;
	return (new);
}

void	add_back(t_list **lst, t_list *new)
{
	t_list	*i;
	t_list	*prv;

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
		prv = i;
		i = i->next;
	}
	i->next = new;
	new->prv = i;
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

void	print_lst(t_list *h)
{
	t_list *i;

	i = h;
	printf("---------------------------------\n");
	while (i)
	{
		printf(">>%s<< ===> %d\n", i->wrd, i->token);
		i = i->next;
	}
	printf("\n---------------------------------\n");
}