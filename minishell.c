/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:23:39 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/31 21:27:57 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	f(void)
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	t_mini	*data;
	char	*res;

	(void)av;
	if (ac != 1 || !env || !*env)
		exit(EXIT_FAILURE);
	while (1)
	{
		res = readline("hi me>> ");
		if (!res)
			break ;
		if (*res)
			add_history(res);
		data = parsing_part(res);
	}
	atexit(f);
	return (0);
}
