/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_qoute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 01:27:11 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/25 17:07:10 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_empty_wrd(t_list *i)
{
	t_list	*swap;

	swap = i->next->next;
	i->wrd = str_join(i->wrd, i->next->wrd);
	if (i->next->token != t_word)
		i->token = i->next->token;
	else
		i->token = i->token;
	free_node(i->next);
	i->next = swap;
}

char	*join_q_wrd(char *s1, char *s2)
{
	char	*res;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (s2[len] && !ft_isspace(s2[len]))
		len++;
	res = malloc(len + ft_strlen(s1) + 1);
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	len = 0;
	while (s2[len] && !ft_isspace(s2[len]))
	{
		res[i] = s2[len];
		i++;
		len++;
	}
	res[i] = '\0';
	return (res);
}

int	cln_space(char *s1)
{
	int	i;

	i = 0;
	while (s1[i] && !ft_isspace(s1[i]))
		i++;
	while (ft_isspace(s1[i]))
		i++;
	return (i);
}

void	split_and_join(t_list **i)
{
	char	*s;
	int		len;
	t_list	*tmp;

	s = (*i)->wrd;
	if (!(*i)->exp_wildcard)
		(*i)->exp_wildcard = need_to_exp_wildards((*i)->wrd);
	(*i)->wrd = join_q_wrd((*i)->wrd, (*i)->next->wrd);
	free(s);
	len = ft_strlen((*i)->next->wrd) - cln_space((*i)->next->wrd);
	if (len != 0)
	{
		s = (*i)->next->wrd;
		(*i)->next->wrd = ft_substr((*i)->next->wrd, \
								cln_space((*i)->next->wrd), len);
		free(s);
		*i = (*i)->next;
	}
	else
	{
		(tmp = (*i)->next) && ((*i)->next = (*i)->next->next);
		if (tmp->next)
			(*i)->next->prv = *i;
		free_node(tmp);
	}
}

int	join_qoute(t_list **head)
{
	t_list	*i;
	t_list	*tmp;

	(delete_if_empty_wrd(head), i = *head);
	while (i && i->next)
	{
		if (is_q(i->token) && !i->next->is_sp && is_q(i->next->token))
		{
			i->wrd = str_join(i->wrd, i->next->wrd);
			i->exp_wildcard = need_to_exp_wildards(i->next->wrd);
			tmp = i->next;
			i->next = i->next->next;
			free_node(tmp);
		}
		else if ((is_q(i->token) || (!i->is_sp && i->next->token == t_word)) \
													&& !i->next->is_sp)
			split_and_join(&i);
		else if (is_q(i->next->token) && i->token == t_word && !i->next->is_sp)
			skip_or_delete(head, &i);
		else
			i = i->next;
	}
	return (0);
}
