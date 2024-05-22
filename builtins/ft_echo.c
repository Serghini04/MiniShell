/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:02:57 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/22 21:34:06 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_mini	*data)
{
	int	i;
	int	j;
	int	v;
	if (!data || !data->cmd[0])
		return ;
	i = 1;
	if (!ft_strcmp(data->cmd[i], "-n"))
	{
		i++;
		v = 0;
	}
	while ( data->cmd[i] && data->cmd[i][0] == '-' && data->cmd[i][1] == 'n')
	{
		j = 2;
		while (data->cmd[i][j] && data->cmd[i][j] == 'n')
			j++;
		if(!data->cmd[i][j])
			v = 0;
		else
			break ;
		i++;
	}
	while (data->cmd[i])
	{
		ft_putstr_fd(data->cmd[i], 1);
		if(data->cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (v == 1)
		ft_putstr_fd("\n", 1);
}
