/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:23:39 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/02 16:59:51 by hidriouc         ###   ########.fr       */
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
	char	**tb_env;
	t_env	*head_myenv;

	(void)av;
	head_myenv = NULL;
	if (ac != 1)
		exit(EXIT_FAILURE);
	data = NULL;
	creat_myenv(&head_myenv, env);
	while (1)
	{
		res = readline("hi me>> ");
		if (!res)
			break ;
		if (*res)
			add_history(res);
		data = parsing_part(res);
		tb_env = creat_tabenv(head_myenv);
		data->head = head_myenv;
		 if(data)
			main_process(data,tb_env);
		// print_t_mini(data);
		// clear_t_mini(&data);
	}
	
	//atexit(f);
	return (0);
}
