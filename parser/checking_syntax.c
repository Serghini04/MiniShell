/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:20:48 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/31 00:21:41 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_empty_wrd(t_list *i)
{
	t_list	*swap;

	swap = i->next->next;
	i->wrd = ft_strjoin(i->wrd, i->next->wrd);
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

int	join_qoute(t_list **head)
{
    t_list	*i;

    delete_if_empty_wrd(head);
    i = *head;
    while (i && i->next)
    {
        if (i->next && is_q(i->token) && !i->next->is_sp && is_q(i->next->token))
        {
            i->wrd = ft_strjoin(i->wrd, i->next->wrd);
            if (i->next->next)
                i->next = i->next->next;
            else
                i->next = NULL;
        }
        else if (i->next && !i->next->is_sp)
        {
            i->wrd = join_q_wrd(i->wrd, i->next->wrd);
            if (ft_strlen(i->next->wrd) - cln_space(i->next->wrd) != 0)
                i->next->wrd = ft_substr(i->next->wrd, cln_space(i->next->wrd), ft_strlen(i->next->wrd) - cln_space(i->next->wrd));
            else
            {
                if (i->next->next)
                    i->next = i->next->next;
                else
                    i->next = NULL;
            }
        }
        else if (i->next && is_q(i->next->token) && !i->next->is_sp)
        {
            i->wrd = ft_strjoin(i->wrd, i->next->wrd);
            if (i->next->next)
                i->next = i->next->next;
            else
                i->next = NULL;
        }
        else
            i = i->next;
    }
    return (0);
}

int	checking_syntax(t_list **head)
{
	t_list	*i;

	i = *head;
	if (i->token == t_pipe)
		return (print_error(head, i), -1);
	while (i)
	{
		if (is_red(i) && i->next->token != t_word \
													&& !is_q(i->next->token))
			return (print_error(head, i), -1);
		if (i->token == t_pipe)
		{
			if (!is_red(i->next) && i->next->token != t_word \
													&& !is_q(i->next->token))
				return (print_error(head, i), -1);
		}
		i = i->next;
	}
	if (i && (is_red(i) || i->token == t_pipe))
		return (print_error(head, i), -1);
	if (join_qoute(head) == -1 || split_cmd(head) == -1)
		return (clear_lst(head), -1);
	return (0);
}
