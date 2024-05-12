/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:02:57 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/11 15:11:52 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(t_mini	*data)
{
	int i = 1;
	int v = 1;
	if (!data)
		return ;
	if (!ft_strcmp(data->cmd[1], "-n"))
	{
		i++;
		v = 0;
	}
	while (data->cmd[i])
	{
		ft_putstr_fd(data->cmd[i], 1);
		if (data->cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (v == 1)
		ft_putstr_fd("\n", 1);
}