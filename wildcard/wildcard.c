/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:53:20 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/21 10:20:39 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*convert_lst_to_line(t_env **head)
{
	char	*res;
	t_env	*h;

	h = *head;
	if (!head)
		return (NULL);
	res = NULL;
	while (h)
	{
		res = str_join(res, h->content);
		if (!res)
			return (free_t_env(head, 1), NULL);
		if (h->next)
		{
			res = str_join(res, " ");
			if (!res)
				return (free_t_env(head, 1), NULL);
		}
		h = h->next;
	}
	return (res);
}

int	is_middle_var(char *line, int *s)
{
	int	i;

	i = *s;
	while (line[i] && line[i] != '*')
		i++;
	if (line[i] == '*')
		return (1);
	return (0);
}

char	*get_expand_wildcards(char *line, int *is_first, int *i, t_env	**head)
{
	char	*res;

	res = NULL;
	if (*is_first)
	{
		*head = save_find_dir(get_name_wildcard(line, *i - 1), head);
		*is_first = 0;
	}
	else if (line[*i] != '*')
		*head = delete_not_need(get_name_wildcard(line, *i - 1), head);
	(*i)++;
	if (line[*i] && line[*i] != '*' && is_middle_var(line, i))
		*head = delete_not_need_middle(get_name_part2(line, i), head);
	else if (line[*i] && line[*i] != '*')
		*head = delete_not_need_part2(get_name_part2(line, i), head);
	if (head && *head)
		return (convert_lst_to_line(head));
	return (ft_strdup(line));
}

char	*replace_wildcards(char *line)
{
	t_env	*head;
	char	*res;
	char	*tmp;
	int		is_first;
	int		i;

	i = 0;
	head = NULL;
	res = NULL;
	is_first = 1;
	while (line[i])
	{
		if (line[i] == '*')
		{
			tmp = res;
			res = get_expand_wildcards(line, &is_first, &i, &head);
			if (!res)
				return (free(line), NULL);
			free(tmp);
		}
		else
			i++;
	}
	free_t_env(&head, 1);
	return (free(line), res);
}

int	wildcards_part(t_list **head)
{
	t_list	*h;
	int		i;

	i = 0;
	h = *head;
	if (h->token == t_word && ft_strchr(h->wrd, '*'))
	{
		h->wrd = replace_wildcards(h->wrd);
		if (!h->wrd)
			return (-1);
	}
	while (h && h->next)
	{
		if (h && h->token != t_heredoc && h->next->token == t_word && \
											ft_strchr(h->next->wrd, '*'))
		{
			h->next->wrd = replace_wildcards(h->next->wrd);
			if (!h->next->wrd)
				return (-1);
		}
		h = h->next;
	}
	return (0);
}
