/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_qoute_part_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 03:51:28 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/25 16:58:05 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*rm_last_join(char *s1)
{
	char	*res;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s1) -1 ;
	if (ft_isspace(s1[len]))
		return (s1);
	while (len >= 0 && !ft_isspace(s1[len]))
		len--;
	while (len >= 0 && ft_isspace(s1[len]))
		len--;
	if (len == -1)
		return (free(s1), NULL);
	res = malloc(len + 2);
	if (!res)
		return (free(s1), NULL);
	while (s1[i] && i <= len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (free(s1), res);
}

void	skip_or_delete(t_list	**head, t_list **i)
{
	t_list	*tmp;

	if (!(*i)->next->exp_wildcard)
		(*i)->next->exp_wildcard = need_to_exp_wildards((*i)->next->wrd);
	(*i)->next->wrd = split_wrd_and_join((*i)->wrd, (*i)->next->wrd);
	(*i)->wrd = rm_last_join((*i)->wrd);
	if (!(*i)->wrd)
	{
		if ((*i)->prv)
			(*i)->prv->next = (*i)->next;
		else
			(*head) = (*i)->next;
		if ((*i)->next)
			(*i)->next->prv = (*i)->prv;
		tmp = *i;
		*i = (*i)->next;
		free(tmp);
	}
	else
		*i = (*i)->next;
}

char	*split_wrd_and_join(char *s1, char *s2)
{
	int		len;
	int		i;
	char	*res;

	len = 0;
	i = ft_strlen(s1) - 1;
	while (i > 0 && !ft_isspace(s1[i]))
	{
		i--;
		len++;
	}
	if (i != 0)
		i++;
	res = malloc(ft_strlen(s2) + len + 2);
	if (!res)
		return (free(s2), NULL);
	len = 0;
	while (s1[i])
		res[len++] = s1[i++];
	i = 0;
	while (s2[i])
		res[len++] = s2[i++];
	res[len] = '\0';
	return (free(s2), res);
}
