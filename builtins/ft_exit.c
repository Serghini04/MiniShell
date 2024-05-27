/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:47:32 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/27 15:55:07 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_mini *data, char *status)
{
	int		var;
	char	**cmd;
	int		len;

	cmd = data->cmd;
	len = 0;
	if (status)
		var = ft_atoi(status);
	if (status && (*status == '+' || *status == '-' ))
		status++;
	while (cmd[len])
		len++;
	if (len > 2 && ft_isdigit(status))
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		save_exit_status(ft_strdup("1"));
		return ;
	}
	if (status && ft_isdigit(status) == 0)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(data->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		var = 255;
	}
	else if (!var && !status)
		var = ft_atoi(save_exit_status(NULL));
	
	clear_t_mini(&data);
	ft_putstr_fd("exit\n", 1);
	exit(var);
}
