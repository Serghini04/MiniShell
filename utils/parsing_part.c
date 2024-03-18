/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 03:41:37 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/18 03:46:01 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_token(char c)
{
	if (c == '\'')
		return (t_signle_q);
	else if (c == '"')
		return (t_double_q);
	else if (c == '<')
		return (t_red_in);
	else if (c == '>')
		return (t_red_out);
	else if (c == '|')
		return (t_pipe);
	return (-1);
}

void	add_to_list(t_list **head, char *input, int s, int pos)
{
	char	*res;
	char	*res_cln;

	res = ft_substr(input, s, pos);
	res_cln = ft_strtrim(res, " \t");
	add_back(head, new_node(res_cln, t_word));
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
	if (!input || !*input)
		return (NULL);
	while (i < len)
	{
		if (check_token(input[i]) != -1)
		{
			add_to_list(&head, input, s, i - s);
			s = i + 1;
		}
		i++;
	}
	return (head);
}

t_list	*parsing_part(char *line)
{
	t_list	*head;
	char 	*res;

	res = ft_strtrim(line, " \t");
	head = tokening(res);
	print_lst(head);
	return (NULL);
}
