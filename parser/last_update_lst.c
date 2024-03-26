/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_update_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:20:02 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/26 21:32:27 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_file(t_list *i, t_mini *node)
{
	if (i->token == t_heredoc)
		node->fd_in = part_heredoc(i, node);
	else if (i->token == t_red_in)
	{
		node->fd_in = open(i->next->wrd, O_RDONLY, 0644);
		if (node->fd_in == -1)
			printf("bash: %s: No such file or directory\n", i->wrd);
	}
	else if (i->token == t_red_out)
	{
		node->fd_out = open(i->next->wrd, O_CREAT | O_WRONLY, 0644);
		if (node->fd_out == -1)
			printf("bash: %s: No such file or directory\n", i->wrd);
	}
	else if (i->token == t_app)
	{
		node->fd_out = open(i->next->wrd, O_APPEND | O_CREAT | O_RDWR, 0644);
		if (node->fd_out == -1)
			printf("bash: %s: No such file or directory\n", i->wrd);
	}
}

t_mini	*add_cmd_to_lst(t_list *i)
{
	t_mini	*node;
	int		index;

	index = 0;
	node = create_node();
	if (!node)
		return (NULL);
	node->cmd = malloc(sizeof(char *) * (len_cmd(i) + 1));
	if (!node->cmd)
		return (free(node), NULL);
	while (i && i->token != t_pipe)
	{
		if (is_red(i))
		{
			open_file(i, node);
			i = i->next;
		}
		else
		{
			node->cmd[index] = ft_strdup(i->wrd);
			index++;
		}
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
