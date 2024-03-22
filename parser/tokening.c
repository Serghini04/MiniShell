/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokening.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:57:09 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/22 03:50:36 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_q(char *input, int c)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (c == input[i])
			return (i);
		i++;
	}
	return (-1);
}

int	add_singl_double_q(t_list **head, char *input, int *i, int *pos)
{
	t_list	*node;
	char	*res;
	int		len;
	char	c;

	c = input[*pos];
	res = ft_substr(input, *i, *pos - *i);
    res = ft_strtrim(res, " \t");
	if (*res)
    	add_back(head, new_node(res, t_word));
	else
		free(res);
	len = len_q(&input[*pos + 1], c);
	if (len == -1)
	{
		printf("syntax error \"%c\"\n", c);
		clear_lst(head);
		return (-1);
	}
	if (c == '\'')
	{
		node = new_node(ft_substr(input, *pos + 1, len), t_signle_q);
		if (input[*pos - 1] == ' ' || input[*pos - 1] == '\t')
			node->is_sp = 1;
		add_back(head, node);
	}
	else
	{
		node = new_node(ft_substr(input, *pos + 1, len), t_double_q);
		if (input[*pos - 1] == ' ' || input[*pos - 1] == '\t')
			node->is_sp = 1;
		add_back(head, node);
	}
	return ((*pos) += len + 1, (*i) = *pos + 1, 1);
}

int	add_token_lst(t_list **head, char *input, int *i, int *s)
{
	char	*res;

    res = ft_substr(input, *s, *i - *s);
	res = ft_strtrim(res, " \t");
	if (*res)
   		add_back(head, new_node(res, t_word));
	else
		free(res);
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
        add_back(head, new_node(ft_strdup(">>"), t_app));
		(*i)++;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
        add_back(head, new_node(ft_strdup("<<"), t_heredoc));
		(*i)++;
	}
    else if (input[*i] != '\0')
	{
        res = ft_substr(input, *i, 1);
        add_back(head, new_node(res, check_token(input[*i])));
    }
	return(*s = *i + 1, 1);
}

t_list	*tokening(char *input)
{
    int		i;
    int		s;
    int		len;
    t_list	*head;

    i = 0;
    s = 0;
    head = NULL;
    len = ft_strlen(input);
    while (i <= len)
    {
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (add_singl_double_q(&head, input, &s, &i) == -1)
				return (NULL);
		}
        if (check_token(input[i]) != -1)
        {
			if (add_token_lst(&head, input, &i, &s) == -1)
				return (NULL);
        }
        i++;
    }
    return (head);
}
