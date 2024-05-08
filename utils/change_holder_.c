/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_holder_.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:31:49 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/08 15:02:27 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_holder_(t_mini *data, t_env *env)
{
	int	i;
	char	*path;
	
	i = 0;
	data->env = creat_tabenv(env);
	if (!(data->next))
	{
		while (data->cmd[i])
			i++;
		path = find_path(data->cmd[i-1], data->env);
		if (path)
			ft_export(ft_strjoin("_=",path), &env);
		else
			ft_export(ft_strjoin("_=",data->cmd[i - 1]), &env);
		data->env = creat_tabenv(env);
	}
}