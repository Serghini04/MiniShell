/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:30:26 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/25 22:05:39 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr(char **res)
{
	int	i;

	i = 0;
	if (!res)
		return ;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
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