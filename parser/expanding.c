/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:19:04 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/27 17:16:58 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*save_exit_status(char *res)
{
	static char	*ret;

	if (res)
	{
		if (ret)
			free(ret);
		ret = res;
	}
	return (ret);
}

int	count_doll(char *str)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i + 1] && str[i] == '$')
			c++;
		i++;
	}
	return (c);
}

int	check_first_node(t_list **i, t_list **head)
{
	t_list	*tmp;
	t_list	*node;

	if (!*head)
		return (0);
	node = *i;
	if (is_expand(node->token, 0) && ft_strchr(node->wrd, '$'))
	{
		node->wrd = replace_dollar_sing(node->wrd);
		if (!node->wrd)
			return (clear_lst(head), -1);
		else if (node->token == t_word && !*node->wrd)
		{
			if (!node->next)
				return (free(node->wrd), free(node), *head = NULL, 0);
			else
			{
				tmp = node;
				(*head) = node->next;
				node->next->prv = NULL;
				(free(tmp->wrd), free(tmp));
			}
		}
	}
	return (1);
}

int	expanding(t_list **head)
{
	t_list	*i;
	int		ret;

	i = *head;
	ret = check_first_node(&i, head);
	i = *head;
	if (ret == 0 || ret == -1)
		return (ret);
	while (i && i->next)
	{
		if (i->token != t_heredoc && is_expand(i->next->token, 0))
		{
			if (ft_strchr(i->next->wrd, '$'))
			{
				i->next->wrd = replace_dollar_sing(i->next->wrd);
				if (!i->next->wrd)
					return (clear_lst(head), -1);
				else if (i->next->token == t_word && !*i->next->wrd)
					delete_node(i->next);
			}
		}
		i = i->next;
	}
	return (0);
}
