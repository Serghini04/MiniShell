/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_update_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:20:02 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/23 21:35:54 by meserghi         ###   ########.fr       */
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

	count = 0;
	i = head;
	while (i && i->token != t_pipe)
	{
		printf("$>>%s\n", i->wrd);
		if (!is_red(i->token))
			count++;
		i = i->next;
	}
	return (count);
}
int	len(char **cmd)
{
	int i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	open_file(t_list *i, t_mini *node)
{
	char	*res;

	if (i->token == t_heredoc)
	{
		node->fd_in = open("/tmp/my_f", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (node->fd_in == -1)
			return (-1);
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
			return (-1);
	}
	else if (i->token == t_red_out)
	{
		node->fd_out = open(i->next->wrd, O_CREAT | O_WRONLY, 0644);
		if (node->fd_out == -1)
			return (-1);
	}
	else if (i->token == t_app)
	{
		node->fd_out = open(i->next->wrd, O_APPEND | O_CREAT | O_RDWR, 0644);
		if (node->fd_out == -1)
			return (-1);
	}
	return (0);
}

int	add_cmd_to_lst(t_list *i)
{
	char	**cmd;
	t_mini	*node;
	int		count;
	int		index;

	count = 0;
	index = 0;
	node = create_node();
	if (!node)
		return (-1);
	cmd = NULL;
	if (i->token == t_word)
	{
		cmd = ft_split(i->wrd, ' ');
		if (!cmd)
			return (-1);
		count = len(cmd);
		i = i->next;
	}
	// node->cmd = malloc(sizeof(char *) * (count + len_cmd(i)));
	// if (!node->cmd)
	// 	return (-1);
	printf("%d\n", count + len_cmd(i));
	exit(1);
	while (cmd[index])
	{
		node->cmd[index] = cmd[index];
		index++;
	}
	while (i && i->token != t_pipe)
	{
		if (is_red(i->token))
		{
			if (open_file(i, node) == -1)
				break;
		}
		node->cmd[index] = i->wrd;
		index++;
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
	printf("===> end <====\n");
	return (data);
}