/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:23:39 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/20 15:55:24 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

int	g_sig_global;

void	f(void)
{
	system("leaks minishell");
}

t_env	*save_env(t_env *env)
{
	static t_env *new_env;

	if (env)
		new_env = env;
	return (new_env);
}

void	handl_sig(int sig)
{
	(void)sig;

	if(g_sig_global == 0)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		save_exit_status(ft_strdup("1"));
	}
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

int	main(int ac, char **av, char **env)
{
	struct	termios term;
	t_mini			*data;
	char			*res;
	t_env			*head;

	(void)av;
	signal(SIGINT, handl_sig);
	signal(SIGQUIT, handle_sigquit);
	save_exit_status(ft_strdup("0"));
	if (ac != 1)
		exit(EXIT_FAILURE);
	data = NULL;
	head = NULL;
	tcgetattr(STDIN_FILENO, &term);
	rl_catch_signals = 0;
	creat_myenv(&head, env);
	while (1)
	{
		res = readline("hi me>> ");
		if (!res)
			return (printf("exit\n"), 1);
		if (*res)
			add_history(res);
		save_env(head);
		data = parsing_part(res);
		if(data)
		{
			g_sig_global = 1;
			main_process(data, &head, &term);
			g_sig_global = 0;
		}
	}
	//  atexit(f);
	return (0);
}
