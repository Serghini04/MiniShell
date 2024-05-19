/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_update_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:20:02 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/14 14:48:53 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_if_open(int fd, int nb)
{
	if (fd != nb)
		close(fd);
}

void	open_file(t_list *i, t_mini *node)
{
	if (i->token != t_heredoc && (node->fd_in == -1 || node->fd_out == -1))
		return ;
	if (i->token == t_heredoc)
		(close_if_open(node->fd_in, 0), node->fd_in = part_heredoc(i, node));
	else if (i->token == t_red_in)
	{
		close_if_open(node->fd_in, 0);
		node->fd_in = open(i->next->wrd, O_RDONLY, 0644);
	}
	else if (i->token == t_red_out)
	{
		close_if_open(node->fd_out, 1);
		node->fd_out = open(i->next->wrd, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	}
	else if (i->token == t_app)
	{
		close_if_open(node->fd_out, 1);
		node->fd_out = open(i->next->wrd, O_APPEND | O_CREAT | O_RDWR, 0644);
	}
}

t_mini	*add_cmd_to_lst(t_list *i)
{
	t_mini	*node;
	int		index;

	(1) && (index = 0, node = create_node());
	if (!node)
		return (NULL);
	node->cmd = malloc(sizeof(char *) * (len_cmd(i) + 1));
	if (!node->cmd)
		return (free(node), NULL);
	while (i && i->token != t_pipe)
	{
		if (is_red(i))
		{
			if (!i->next)
			{
				(1) && (i = i->next, node->fd_in = -1);
				continue ;
			}
			(1) && (open_file(i, node), i = i->next);
		}
		else if (i->wrd)
			node->cmd[index++] = ft_strdup(i->wrd);
		i = i->next;
	}
	return (node->cmd[index] = NULL, node);
}

t_mini	*last_update_lst(t_list *head)
{
	t_mini	*data;
	t_list	*i;
	t_list	*s;

	i = head;
	s = head;
	data = NULL;
	while (i)
	{
		if (i->token == t_pipe)
		{
			add_back_t_mini(&data, add_cmd_to_lst(s));
			s = i->next;
		}
		i = i->next;
	}
	add_back_t_mini(&data, add_cmd_to_lst(s));
	return (data);
}
