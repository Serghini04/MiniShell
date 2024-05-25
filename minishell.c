/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:23:39 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/25 23:25:13 by meserghi         ###   ########.fr       */
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
	else if (g_sig_global == 2)
	{
		close(0);
		save_exit_status(ft_strdup("1"));
	}
}

// void	handle_sigquit(int sig)
// {
// 	(void)sig;
// 	save_exit_status(ft_strdup("131"));
// }

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
	signal(SIGQUIT, SIG_IGN);
	save_exit_status(ft_strdup("0"));
	rl_catch_signals = 0;
}

void f(void)
{
	system ("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	t_mini			*data;
	char			*res;
	t_env			*head;
	struct termios	term;

	data = NULL;
	if (!isatty(0))
		return (1);
	ft_handel_aergs(ac, av, &term, &head);
	creat_myenv(&head, env);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	while (1)
	{
		res = readline("hi me>> ");
		if (!res)
			return (ft_putstr_fd("exit\n", 2), ft_atoi(save_exit_status(0)));
		if (*res)
			add_history(res);
		save_env(head);
		g_sig_global = 0;
		data = parsing_part(res);
			if (g_sig_global == -1)
				continue ;
		if (data)
		{
			main_process(data, &head, &term);
			g_sig_global = 0;
			clear_t_mini(&data);
		}
	}
	return (0);
}
