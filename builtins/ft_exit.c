/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:47:32 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/25 12:44:34 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_mini *data, char *status)
{
	int	var;

	if (status)
		var = (ft_atoi(status) % 256);
	else
		var = ft_atoi(save_exit_status(NULL));
	clear_t_mini(&data);
	exit(var);
}
