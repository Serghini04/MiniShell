/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:47:32 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/31 11:06:07 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handel_input(t_mini *data, char *status, int *var)
{
	char	**cmd;
	int		len;

	len = 0;
	cmd = data->cmd;
	if (status && (*status == '+' || *status == '-' ))
		status++;
	while (cmd[len])
		len++;
	if (len > 2 && ft_isdigit(status))
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		return (save_exit_status(ft_strdup("1")), 1);
	}
	if (status && ft_isdigit(status) == 0)
	{
		(ft_putstr_fd("exit\n", 2), ft_putstr_fd("bash: exit: ", 2));
		ft_putstr_fd(data->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		*var = 255;
	}
	else
		*var = ft_atoi(save_exit_status(NULL));
	return (0);
}

void	ft_exit(t_mini *data, char *status, int flag)
{
	int		var;

	var = 0;
	if (status)
		var = ft_atoi(status);
	if (ft_handel_input(data, status, &var))
		return ;
	clear_t_mini(&data);
	if (flag)
		ft_putstr_fd("exit\n", 1);
	exit(var);
}
