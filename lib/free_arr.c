/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:30:26 by meserghi          #+#    #+#             */
/*   Updated: 2024/06/02 11:04:25 by hidriouc         ###   ########.fr       */
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
	res = NULL;
}

void	print_t_mini(t_mini *data)
{
	t_mini	*i;
	int		index;

	i = data;
	index = 1;
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

void	print_lst(t_list *h)
{
	t_list	*i;

	i = h;
	printf("---------------------------------\n");
	printf("str---token---exp_wildcard\n");
	printf("---------------------------------\n");
	while (i)
	{
		printf(">>%s<< ===> %d ==> %d\n", i->wrd, i->token, i->exp_wildcard);
		i = i->next;
	}
	printf("\n---------------------------------\n");
}
