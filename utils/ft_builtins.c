/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:00:38 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/27 10:39:25 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtins(t_mini *data, t_env *lin_env, struct termios *saver, t_fd *fd)
{
	fd->fdin = 0;
	tcgetattr(STDIN_FILENO, saver);
	data->env = creat_tabenv(lin_env);
	if (ft_check_if_builtin(data, fd, &lin_env) && !data->next)
		return (red_fd_parent(fd), 1);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	return (0);
}
