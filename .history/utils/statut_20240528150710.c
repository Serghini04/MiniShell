/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:06:58 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/28 15:07:10 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	return_status(int *tb, int nb_pids)
{
	int		ret;
	char	*res;
	int		i;

	i = 0;
	while (waitpid(tb[i], &ret, 0) != -1 && i < nb_pids)
		i++;
	if (WIFSIGNALED(ret))
	{
		res = ft_itoa(128 + WTERMSIG(ret));
		if (WTERMSIG(ret) == 2)
			ft_putstr_fd("\n", 1);
		if (WTERMSIG(ret) == 3)
			ft_putstr_fd("Quit: 3\n", 1);
	}
	else
		res = ft_itoa(WEXITSTATUS(ret));
	if (!res)
		return ;
	save_exit_status(res);
}
