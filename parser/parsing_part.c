/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 03:41:37 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/25 21:09:36 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// i wanna to clean my code and fix memory leaks ...
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

int join_qoute(t_list **head)
{
	t_list	*i;
	t_list	*swap;

	i = *head;
	while (i)
	{
		if (i->next && !*i->wrd && !*i->next->wrd)
		{
			swap = i->next;
			i->next = i->next->next;
			free_node(swap);
		}
		else
			i = i->next;
	}
	i = *head;
	while (i && i->next)
	{
		if (i->token == t_signle_q || i->token == t_double_q)
		{
			if (i->next->token == t_word && !i->next->is_sp)
			{
				swap = i->next->next;
				i->wrd = ft_strjoin(i->wrd, i->next->wrd);
				i->token = i->next->token;
				free_node(i->next);
				i->next = swap;
			}
		}
		if (i && i->next && (i->next->token == t_signle_q || i->next->token == t_double_q))
		{
			if (i->token == t_word && !i->next->is_sp)
			{
				swap = i->next->next;
				i->wrd = ft_strjoin(i->wrd, i->next->wrd);
				i->token = i->next->token;
				free_node(i->next);
				i->next = swap;
			}
		}
		i = i->next;
	}
	return (0);
}

void	add_split_lst(char **cmd, t_list **head, t_list **root)
{
	t_list	*new_head;
	t_list	*last;
	t_list	*swap;
	int		i;

	i = 0;
	new_head = NULL;
	while (cmd[i])
	{
		add_back(&new_head, new_node(ft_strdup(cmd[i]), t_word));
		i++;
	}
	last = last_lst(new_head);
	swap = (*head);
	last->next = (*head)->next;
	if ((*head)->prv)
		(*head)->prv->next = new_head;
	else
		(*root) = new_head;
	free_arr(cmd);
	(*head) = (*head)->next;
	free_node(swap);
}

int	split_wrd(t_list **head)
{
	t_list	*i;
	char	**cmd;

	i = *head;
	while (i)
	{
		if (i->token == t_word && find_space(i->wrd))
		{
			cmd = ft_split(i->wrd, ' ');
			if (!cmd)
				return (-1);
			add_split_lst(cmd, &i, head);
		}
		else
			i = i->next;
	}
	return (0);
}


int	checking_syntax(t_list **head)
{
	t_list	*i;

	i = *head;
	if (i->token == t_pipe)
		return (print_error(head, i), -1);
	while (i->next)
	{
		if (is_red(i) && i->next->token != t_word \
													&& !is_q(i->next->token))
			return (print_error(head, i), -1);
		if (i->token == t_pipe)
		{
			if (!is_red(i->next) && i->next->token != t_word \
													&& !is_q(i->next->token))
				return (print_error(head, i), -1);
		}
		i = i->next;
	}
	if (is_red(i) || i->token == t_pipe)
		return (print_error(head, i), -1);
	if (join_qoute(head) == -1 || split_wrd(head) == -1)
		return (clear_lst(head), -1);
	return (0);
}

void	print_t_mini(t_mini *data)
{
	t_mini	*i;

	i = data;
	int index = 1;
	printf("=========================================\n");
	printf("|cmd ...|	Arg    | fd_in	| fd_out |\n");
	printf("==========================================\n");
	while (i)
	{
		index = 0;
		printf("|%s	|", i->cmd[0]);
		while (i->cmd[index++])
			printf("%s ", i->cmd[index]);
		printf("	|%d	|	%d|\n", i->fd_in, i->fd_out);
		i = i->next;
	}
	printf("==========================================\n");
}

t_mini	*parsing_part(char *line)
{
	t_list	*head;
	t_mini	*data;
	char 	*res;

	data = NULL;
	res = ft_strtrim(line, " \t");
	if (!res)
		return (free(res), NULL);
	head = tokening(res);
	if (!head)
		return (clear_lst(&head), free(res), NULL);
	free(res);
	if (checking_syntax(&head) == -1)
		return (NULL);
	data = last_update_lst(head);
	print_t_mini(data);
	// clear_t_mini(&data);
	return (NULL);
}
