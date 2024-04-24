/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:01:40 by meserghi          #+#    #+#             */
/*   Updated: 2024/04/22 18:39:30 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_cmd(t_list *head)
{
	t_list	*i;
	int		count;
	int		s;

	count = 0;
	i = head;
	s = 0;
	while (i && i->token != t_pipe)
	{
		if (!is_red(i))
			count++;
		else
			s++;
		i = i->next;
	}
	return (count - s);
}

int	len(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

char	*expand_heredoc(char *str, int token)
{
	char	*res;

	res = str_join(str, "\n");
	if (is_expand(token, 1) && ft_strchr(res, '$'))
	{
		res = replace_dollar_sing(res);
		return (res);
	}
	return (res);
}

int	part_heredoc(t_list *i, t_mini *node)
{
	char	*res;
	char	*line_heredoc;
	int		v;

	v = 1;
	if (node->fd_in == -1)
		v = 0;
	node->fd_in = open("/tmp/my_f", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (node->fd_in == -1)
		return (printf("bash: %s: No such file or directory\n", i->wrd), -1);
	while (1)
	{
		res = readline(">");
		if (!res || !ft_strcmp(res, i->next->wrd))
			break ;
		line_heredoc = expand_heredoc(res, i->next->token);
		write(node->fd_in, line_heredoc, ft_strlen(line_heredoc));
		free(line_heredoc);
	}
	close(node->fd_in);
	if (!v)
		node->fd_in = -1;
	else
		node->fd_in = open("/tmp/my_f", O_RDWR, 0644);
	return (free(res), node->fd_in);
}
