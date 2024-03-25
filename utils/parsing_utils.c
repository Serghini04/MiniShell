/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:01:40 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/25 22:02:47 by meserghi         ###   ########.fr       */
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

int	part_heredoc(t_list *i, t_mini *node)
{
	char	*res;

	node->fd_in = open("/tmp/my_f", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (node->fd_in == -1)
		printf("bash: %s: No such file or directory\n", i->wrd);
	while (1)
	{
		res = readline(">");
		if (!res || !ft_strcmp(res, i->next->wrd))
			break ;
	}
	return (node->fd_in);
}