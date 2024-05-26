/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:47:32 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/26 14:57:45 by meserghi         ###   ########.fr       */
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
	{
		if (*status == '+')
			status++;
	}
	while (cmd[len])
		len++;
	if (len > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		save_exit_status(ft_strdup("1"));
		return ;
	}
	if (status && !ft_isdigit(status))
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(data->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		if (ft_atoi(status) < 0)
			var = 156;
		else
			var = 255;
	}
	else if (status)
		var = ft_atoi(status) % 256;
	else
		var = ft_atoi(save_exit_status(NULL));
	clear_t_mini(&data);
	exit(var);
}
