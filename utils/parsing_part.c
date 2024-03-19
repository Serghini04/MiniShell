/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 03:41:37 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/19 16:19:15 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_token(char c)
{
	if (c == '<')
		return (t_red_in);
	else if (c == '>')
		return (t_red_out);
	else if (c == '|')
		return (t_pipe);
	else if (c == '\0')
		return (t_last);
	return (-1);
}

int	len_c(char *input, int c)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (c == input[i])
			return (i);
		i++;
	}
	printf("syntax error \"%c\"", c);
	exit(1);
}

void	add_singl_double_q(t_list **head, char *input, int *i, int *pos)
{
	char	*res;
	int		len;
	char	c;

	c = input[*pos];
	res = ft_substr(input, *i, *pos - *i);
    res = ft_strtrim(res, " \t");
	if (*res)
    	add_back(head, new_node(res, t_word));
	len = len_c(&input[*pos + 1], c);
	if (c == '\'')
		add_back(head, new_node(ft_substr(input, *pos + 1, len), t_signle_q));
	else
		add_back(head, new_node(ft_substr(input, *pos + 1, len), t_double_q));
	(*pos) += len + 1;
	(*i) = *pos + 1;
}

t_list	*tokening(char *input)
{
    int		i;
    int		s;
    int		len;
	char	*res;
    t_list	*head;

    i = 0;
    s = 0;
    head = NULL;
    len = ft_strlen(input);
    if (!input || !*input)
        return (NULL);
    while (i <= len)
    {
		if (input[i] == '\'' || input[i] == '\"')
			add_singl_double_q(&head, input, &s, &i);
        if (check_token(input[i]) != -1)
        {
            res = ft_substr(input, s, i - s);
            res = ft_strtrim(res, " \t");
			if (*res)
           		add_back(&head, new_node(res, t_word));
			if (input[i] == '>' && input[i + 1] == '>')
			{
                add_back(&head, new_node(ft_strdup(">>"), t_app));
				i++;
			}
			else if (input[i] == '<' && input[i + 1] == '<')
			{
                add_back(&head, new_node(ft_strdup("<<"), t_heredoc));
				i++;
			}
            else if (input[i] != '\0') {
                res = ft_substr(input, i, 1);
                add_back(&head, new_node(res, check_token(input[i])));
            }
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
