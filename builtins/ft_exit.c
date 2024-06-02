/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:47:32 by hidriouc          #+#    #+#             */
/*   Updated: 2024/06/02 18:41:27 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handel_input(t_mini *data, char *status, long long *var, int *flag)
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
		ft_putstr_fd("exit\nbash: exit: too many arguments\n", 2);
		return (save_exit_status(ft_strdup("1")), 1);
	}
	if (status && ft_isdigit(status) == 0)
	{
		*flag = 0;
		(ft_putstr_fd("exit\n", 2), ft_putstr_fd("bash: exit: ", 2));
		ft_putstr_fd(data->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		*var = 255;
	}
	else if (!data->cmd[1])
		*var = ft_atoi(save_exit_status(NULL));
	return (0);
}

void	ft_exit(t_mini *data, char *status, int flag)
{
	long long	var;

	var = 0;
	if (ft_handel_input(data, status, &var, &flag))
		return ;
	if (!var && status)
		var = advance_atoi(status);
	if (flag)
		ft_putstr_fd("exit\n", 1);
	if (var == -1)
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(data->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		var = 255;
	}
	free_arr(data->env);
	clear_t_mini(&data);
	exit(var);
}
