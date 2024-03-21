/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 03:41:37 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/21 00:47:04 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// fix redirection for syntax error.

// start parsing like this :
/* Example For the line : cat < "Makefile" | grep something > outfile | wc -l < outfile */
//	 /---------------------------------------------------\
//   | PIPE_LINE|  CMD|      ARGS|   IN_REDIR|  OUT_REDIR|
//   |---------------------------------------------------|
//   |        00|  cat|      NULL| "Makefile"|       NULL|
//   |        01| grep| something|       NULL|    outfile|
//   |        02|   wc|        -l|    outfile|       NULL|
//   \---------------------------------------------------/
// ...

// i wanna to clean my code and fix memory leaks ...


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
	return (-1);
}

int	add_singl_double_q(t_list **head, char *input, int *i, int *pos)
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
	if (len == -1)
	{
		printf("syntax error \"%c\"\n", c);
		clear_lst(head);
		return (-1);
	}
	if (c == '\'')
		add_back(head, new_node(ft_substr(input, *pos + 1, len), t_signle_q));
	else
		add_back(head, new_node(ft_substr(input, *pos + 1, len), t_double_q));
	(*pos) += len + 1;
	(*i) = *pos + 1;
	return (1);
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
		{
			if (add_singl_double_q(&head, input, &s, &i) == -1)
				return (NULL);
		}
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
int	is_token(int c)
{
	if (c == t_pipe)
		return (1);
	else if (c == t_red_in)
		return (1);
	else if (c == t_red_out)
		return (1);
	else if (c == t_app)
		return (1);
	else if (c == t_heredoc)
		return (1);
	return (0);
}

int is_redirection(int c)
{
	if (c == t_red_in)
		return (1);
	else if (c == t_red_out)
		return (1);
	else if (c == t_app)
		return (1);
	else if (c == t_heredoc)
		return (1);
	return (0);
}

void	checking_syntax(t_list **head)
{
	t_list	*i;

	i = *head;
	if (!head || !*head)
		return ;
	if (i->token == t_pipe)
	{
		printf("syntax error \"%c\"\n", i->token);
		clear_lst(head);
		return ;
	}
	while (i->next)
	{
		if (is_token(i->token))
		{
			if (i->next->token != t_word && i->next->token != t_double_q\
				&& i->next->token != t_signle_q && (!is_redirection(i->next->token) && is_redirection(i->token)))
			{
				printf("syntax error \"%s\"\n", i->wrd);
				clear_lst(head);
				return ;
			}
		}
		i = i->next;
	}
	if (is_token(i->token))
	{
		printf("syntax error \"%s\"\n", i->wrd);
		clear_lst(head);
	}
}

t_list	*parsing_part(char *line)
{
	t_list	*head;
	char 	*res;

	res = ft_strtrim(line, " \t");
	head = tokening(res);
	checking_syntax(&head);
	print_lst(head);
	return (NULL);
}
