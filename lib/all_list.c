/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:47:40 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/18 00:36:46 by meserghi         ###   ########.fr       */
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
	i->next = new;
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
		free(i->wrd);
		free(i);
		i = swap;
	}
	i = NULL;
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