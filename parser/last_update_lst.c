/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_update_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:20:02 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/23 03:23:20 by meserghi         ###   ########.fr       */
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

int	len_cmd(t_list *i)
{
	int	count;

	count = 0;
	while (i && i->token != t_pipe)
	{
		if (is_red(i->token))
			break ;
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

int	add_cmd_to_lst(t_list *i)
{
	char	**cmd;
	t_mini	*node;
	int		count;
	int		index;

	count = 0;
	node = NULL;
	cmd = NULL;
	index = 0;
	node = malloc(sizeof(t_mini));
	if (!node)
		return (-1);
	if (i->wrd)
	{
		cmd = ft_split(i->wrd, ' ');
		if (!cmd)
			return (-1);
		count = len(cmd);
		i = i->next;
	}
	node->cmd = malloc(sizeof(char *) * (count + len_cmd(i)));
	if (!node->cmd)
		return (-1);
	while (cmd[index])
	{
		node->cmd[index] = cmd[index];
		index++;
	}
	while (i->next && i->token != t_pipe)
	{
		node->cmd[index] = i->wrd;
		index++;
		i = i->next;
	}
	node->cmd[index] = NULL;
	return (0);
}

t_mini	*last_update_lst(t_list **head)
{
	t_mini	*data;
	t_list	*i;
	t_list	*s;

	i = *head;
	s = *head;
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