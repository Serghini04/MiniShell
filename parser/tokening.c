/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokening.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:57:09 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/31 10:44:32 by meserghi         ###   ########.fr       */
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

t_list	*add_single_or_double_q(char *input, int pos, int len)
{
	t_list	*node;

	if (input[pos] == '\'')
	{
		node = new_node(ft_substr(input, pos + 1, len), t_signle_q);
		if (pos > 0 && input[pos - 1] != ' ' && input[pos - 1] != '\t')
			node->is_sp = 0;
	}
	else
	{
		node = new_node(ft_substr(input, pos + 1, len), t_double_q);
		if (pos > 0 && input[pos - 1] != ' ' && input[pos - 1] != '\t')
			node->is_sp = 0;
	}
	return (node);
}

int	add_singl_double_q(t_list **head, char *input, int *i, int *pos)
{
	t_list	*node;
	char	*res;
	int		len;

	res = ft_strtrim(ft_substr(input, *i, *pos - *i), " \t");
	if (!res)
		return (clear_lst(head), -1);
	if (*res)
	{
		node = new_node(res, t_word);
		if (*pos > 0 && input[*i] != ' ' && input[*i] != '\t')
			node->is_sp = 0;
		add_back(head, node);
	}
	else
		free(res);
	len = len_q(&input[*pos + 1], input[*pos]);
	if (len == -1)
	{
		printf("syntax error \"%c\"\n", input[*pos]);
		(save_exit_status(ft_strdup("258")), clear_lst(head));
		return (-1);
	}
	add_back(head, add_single_or_double_q(input, *pos, len));
	return ((*pos) += len + 1, (*i) = *pos + 1, 0);
}

int	add_token_lst(t_list **head, char *input, int *i, int *s)
{
	char	*res;
	t_list	*node;

	res = ft_strtrim(ft_substr(input, *s, *i - *s), " \t");
	if (*res)
	{
		node = new_node(res, t_word);
		if (*i > 0 && input[*s] != ' ' && input[*s] != '\t')
			node->is_sp = 0;
		add_back(head, node);
	}
	else
		free(res);
	if (input[*i] == '>' && input[*i + 1] == '>')
		(add_back(head, new_node(ft_strdup(">>"), t_app)), (*i)++);
	else if (input[*i] == '<' && input[*i + 1] == '<')
		(add_back(head, new_node(ft_strdup("<<"), t_heredoc)), (*i)++);
	else if (input[*i] != '\0')
		add_back(head, new_node(ft_substr(input, *i, 1), \
										check_token(input[*i])));
	return (*s = *i + 1, 0);
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
