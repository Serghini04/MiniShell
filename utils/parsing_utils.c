/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:01:40 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/28 14:30:02 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_cmd(t_list *head)
{
	t_list	*i;
	int		count;

	count = 0;
	i = head;
	while (i && i->token != t_pipe)
	{
		if (!is_red(i) || (is_red(i) && !i->next))
			count++;
		i = i->next;
	}
	return (count);
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
	if (!res)
		return (NULL);
	if (is_expand(token, 1) && ft_strchr(res, '$'))
	{
		res = replace_dollar_sing(res);
		return (res);
	}
	return (res);
}

int	open_here_doc_file(int *save, int *fd_in)
{
	unlink("/tmp/my_f");
	*fd_in = open("/tmp/my_f", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_in == -1)
		return (printf("bash: open here_doc error\n"), -1);
	*save = open("/tmp/my_f", O_RDONLY, 0644);
	if (*save == -1)
		return (printf("bash: open here_doc error\n"), close(*fd_in), -1);
	unlink("/tmp/my_f");
	return (*save);
}

int	part_heredoc(t_list *i, t_mini *node)
{
	extern int	g_sig_global;
	char		*res;
	char		*line_heredoc;
	int			v;
	int			save;

	v = (node->fd_in != -1) * 1;
	save = open_here_doc_file(&save, &node->fd_in);
	if (save == -1)
		return (-1);
	while (!g_sig_global && isatty(0))
	{
		signal(SIGINT, fn);
		res = readline(">");
		if (!res || !ft_strcmp(res, i->next->wrd))
			break ;
		line_heredoc = expand_heredoc(res, i->next->token);
		write(node->fd_in, line_heredoc, ft_strlen(line_heredoc));
		free(line_heredoc);
	}
	if (!v)
		save = -1;
	return (close(node->fd_in), free(res), save);
}
