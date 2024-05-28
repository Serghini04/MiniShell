/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_update_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:20:02 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/28 12:14:01 by hidriouc         ###   ########.fr       */
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

int	init_new_node(int *index, t_mini **node, int *fd, t_list *i)
{
	*index = 0;
	*node = create_node();
	if (!*node)
		return (-1);
	(*node)->cmd = malloc(sizeof(char *) * (len_cmd(i) + 1));
	if (!(*node)->cmd)
		return (free(*node), 0);
	*fd = dup(0);
	if (*fd == -1)
		return (free((*node)->cmd), free(*node), -1);
	return (0);
}

t_mini	*add_cmd_to_lst(t_list *i, int *hand_signal)
{
	extern int	g_sig_global;
	t_mini		*node;
	int			fd;
	int			index;

	if (init_new_node(&index, &node, &fd, i) == -1)
		return (NULL);
	while (!*hand_signal && i && i->token != t_pipe)
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
		if (g_sig_global == -1)
			*hand_signal = 1;
		i = i->next;
	}
	return (last_update_node(&fd, &node, &index));
}

t_mini	*last_update_lst(t_list *head)
{
	t_mini	*data;
	t_list	*i;
	t_list	*s;
	int		hand_signal;

	i = head;
	s = head;
	hand_signal = 0;
	data = NULL;
	while (i)
	{
		if (i->token == t_pipe)
		{
			add_back_t_mini(&data, add_cmd_to_lst(s, &hand_signal));
			s = i->next;
		}
		i = i->next;
	}
	add_back_t_mini(&data, add_cmd_to_lst(s, &hand_signal));
	if (hand_signal)
		clear_t_mini(&data);
	return (data);
}
