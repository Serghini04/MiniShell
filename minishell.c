/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:23:39 by meserghi          #+#    #+#             */
/*   Updated: 2024/06/02 19:27:17 by hidriouc         ###   ########.fr       */
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

void	ft_handel_args(int ac, char **av, struct termios *term, t_env **head)
{
	(void)av;
	*head = NULL;
	rl_catch_signals = 0;
	if (ac != 1 || !isatty(0))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd("whithout argumments please !!\n", 2);
		exit(EXIT_FAILURE);
	}
	if (tcgetattr(STDIN_FILENO, term) != 0)
		perror("tcgetattr()error");
	signal(SIGINT, handl_sig);
	signal(SIGQUIT, SIG_IGN);
	save_exit_status(ft_strdup("0"));
	if (tcsetattr(STDIN_FILENO, TCSANOW, term) != 0)
		perror("tcgetattr() error");
}

int	main(int ac, char **av, char **env)
{
	struct termios	term;
	t_mini			*data;
	char			*res;
	t_env			*head;

	data = NULL;
	ft_handel_args(ac, av, &term, &head);
	creat_myenv(&head, env);
	while (1)
	{
		res = readline("hi me>> ");
		signal(SIGINT, handl_sig);
		if (!res)
			return (appell_clear(&head), ft_atoi(save_exit_status(NULL)));
		if (*res)
			add_history(res);
		save_env(head);
		data = parsing_part(res);
		if (data)
		{
			main_process(data, &head, &term);
			clear_t_mini(&data);
		}
	}
	return (0);
}
