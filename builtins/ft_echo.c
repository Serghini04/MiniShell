/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:02:57 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/31 10:48:48 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handel_in(t_mini *data, int *i, int *v)
{
	int	j;

	*v = 1;
	if (!data || !data->cmd[0])
		return (0);
	*i = 1;
	if (!ft_strcmp(data->cmd[*i], "-n"))
	{
		(*i)++;
		*v = 0;
	}
	while (data->cmd[*i] && data->cmd[*i][0] == '-' && data->cmd[*i][1] == 'n')
	{
		j = 2;
		while (data->cmd[*i][j] && data->cmd[*i][j] == 'n')
			j++;
		if (!data->cmd[*i][j])
			*v = 0;
		else
			break ;
		(*i)++;
	}
	return (1);
}

void	ft_echo(t_mini	*data)
{
	int	i;
	int	v;

	if (!ft_handel_in(data, &i, &v))
		return ;
	while (data->cmd[i])
	{
		ft_putstr_fd(data->cmd[i], 1);
		if (data->cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (v == 1)
		ft_putstr_fd("\n", 1);
	save_exit_status(ft_strdup("0"));
}
