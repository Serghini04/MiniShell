/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 03:41:37 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/18 18:17:55 by meserghi         ###   ########.fr       */
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
	else if (c == '\0')
		return (t_last);
	return (-1);
}

void	add_to_list(t_list **head, char *input, int s, int pos)
{
    char	*res;
    char	*res_cln;

    res = ft_substr(input, s, pos);
    res_cln = ft_strtrim(res, " \t");
    add_back(head, new_node(res_cln, t_word));
    if (input[s + pos] != ' ' && input[s + pos] != '\0') {
        res = ft_substr(input, s + pos, 1);
        add_back(head, new_node(res, check_token(input[s + pos])));
    }
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
        if (check_token(input[i]) != -1)
        {
            res = ft_substr(input, s, i - s);
			if (!res)
				exit(1);
            res = ft_strtrim(res, " \t");
			if (!res)
				return (NULL);
			if (*res)
           		add_back(&head, new_node(res, t_word));
			else
				free(res);
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
