/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:23:39 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/25 10:48:39 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_global;

t_env	*save_env(t_env *env)
{
	static t_env	*new_env;

	if (env)
		new_env = env;
	return (new_env);
}

void	handl_sig(int sig)
{
	(void)sig;
	if (g_sig_global == 0)
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

void	ft_handel_aergs(int ac, char **av, struct termios *term, t_env **head)
{
	(void)av;
	*head = NULL;
	if (ac != 1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(EXIT_FAILURE);
	}
	tcgetattr(STDIN_FILENO, term);
	signal(SIGINT, handl_sig);
	signal(SIGQUIT, handle_sigquit);
	save_exit_status(ft_strdup("0"));
	rl_catch_signals = 0;
}

int	main(int ac, char **av, char **env)
{
	t_mini			*data;
	char			*res;
	t_env			*head;
	struct termios	term;

	data = NULL;
	ft_handel_aergs(ac, av, &term, &head);
	creat_myenv(&head, env);
	while (1)
	{
		res = readline("hi me>> ");
		if (!res)
			return (ft_putstr_fd("exit\n", 2), 1);
		if (*res)
			add_history(res);
		save_env(head);
		data = parsing_part(res);
		if (data)
		{
			g_sig_global = 1;
			main_process(data, &head, &term);
			g_sig_global = 0;
			clear_t_mini(&data);
		}
	}
	return (0);
}
