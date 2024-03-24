/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_update_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:20:02 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/24 01:44:26 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// start parsing like this :
/* Example For the line : cat < "Makefile" | grep something > outfile | wc -l < outfile */
//	 /---------------------------------------------------\
//   | PIPE_LINE|  CMD|      ARGS|   IN_REDIR|  OUT_REDIR|
//   |---------------------------------------------------|
//   |        00|  cat|      NULL| "Makefile"|       NULL|
//   |        01| grep| something|       NULL|    outfile|
//   |        02|   wc|        -l|    outfile|       NULL|
//   \---------------------------------------------------/

// ls | ls

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
	int i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	open_file(t_list *i, t_mini *node)
{
	char	*res;

	if (i->token == t_heredoc)
	{
		node->fd_in = open("/tmp/my_f", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (node->fd_in == -1)
			printf("bash: %s: No such file or directory\n", i->wrd);
		while (1)
		{
			res = readline(">");
			if (!res || !ft_strcmp(res, i->next->wrd))
				break;
		}
	}
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

int	add_cmd_to_lst(t_list *i)
{
	char	**cmd;
	t_mini	*node;
	int		index;

	index = 0;
	node = create_node();
	if (!node)
		return (-1);
	cmd = NULL;
	node->cmd = malloc(sizeof(char *) * len_cmd(i));
	if (!node->cmd)
		return (-1);
	while (i->token != t_pipe)
	{
		if (is_red(i))
		{
			open_file(i, node);
			printf("1\n");
		}
		else if (is_red(i->prv))
		{
			node->cmd[index] = i->wrd;
			printf(">>%s\n", node->cmd[index]);
			index++;
		}
		i = i->next;
	}
	node->cmd[index] = NULL;
	return (0);
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
			add_cmd_to_lst(s);
			s = i->next;
		}
		i = i->next;
	}
	return (data);
}