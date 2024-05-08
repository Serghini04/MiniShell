/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:23:39 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/08 14:48:03 by hidriouc         ###   ########.fr       */
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
	int		flag;
	t_env	*head;

	(void)av;
	flag = 0;
	save_exit_status(ft_strdup("0"));
	if (ac != 1)
		exit(EXIT_FAILURE);
	data = NULL;
	head = NULL;
	creat_myenv(&head, env);
	while (1)
	{
		res = readline("hi me>> ");
		if (!res)
			break ;
		if (*res)
			add_history(res);
		data = parsing_part(res);
		if(data)
			main_process(data, head);
		clear_t_mini(&data);
	}
	printf("exit\n");
	atexit(f);
	return (0);
}
