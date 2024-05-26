/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_not_need.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:00:44 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/26 14:55:55 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*delete_not_need_middle(char *name_var, t_env **head)
{
	t_env	*new_head;
	t_env	*h;

	new_head = NULL;
	if (!name_var)
		return (free_t_env(head, 1), NULL);
	if (!head)
		return (free(name_var), NULL);
	h = *head;
	while (h)
	{
		if (ft_strstr(h->content, name_var))
			ft_lstadd_back(&new_head, ft_lstnew(h->content));
		h = h->next;
	}
	free(name_var);
	free_t_env(head, 0);
	return (new_head);
}

t_env	*delete_not_need(char *name_var, t_env **head)
{
	t_env	*h;
	t_env	*new_head;

	new_head = NULL;
	if (!name_var)
		return (free_t_env(head, 1), NULL);
	if (!head)
		return (free(name_var), NULL);
	h = *head;
	while (h)
	{
		if (!ft_strncmp(h->content, name_var, ft_strlen(name_var)))
			ft_lstadd_back(&new_head, ft_lstnew(ft_strdup(h->content)));
		h = h->next;
	}
	free(name_var);
	free_t_env(head, 1);
	return (new_head);
}

t_env	*delete_not_need_part2(char *name_var, t_env **head)
{
	t_env	*new_head;
	t_env	*h;

	new_head = NULL;
	if (!name_var)
		return (free_t_env(head, 1), NULL);
	if (!head)
		return (free(name_var), NULL);
	h = *head;
	while (h)
	{
		if (!reverse_cmp(h->content, name_var, ft_strlen(name_var)))
			ft_lstadd_back(&new_head, ft_lstnew(h->content));
		h = h->next;
	}
	free(name_var);
	free_t_env(head, 0);
	return (new_head);
}

int	check_node(t_list *h, int *need_split)
{
	*need_split = 0;
	if (h && h->exp_wildcard && ft_strchr(h->wrd, '*'))
	{
		*need_split = 1;
		h->wrd = replace_wildcards(h->wrd);
		if (!h->wrd)
			return (-1);
	}
	return (0);
}
