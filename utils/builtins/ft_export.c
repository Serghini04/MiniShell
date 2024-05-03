/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:57:33 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/02 15:01:05 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export(t_env	**head, t_mini	*data)
{
	int		flag;
	t_env	*tmp;
	char	**spli_arg;

	flag = 0;
	tmp = *head;
	while (tmp)
	{
		spli_arg = ft_split(data->cmd[1], '=');
		if(!ft_strncmp(tmp->name, spli_arg[0], ft_strlen(spli_arg[0])))
		{
			free(tmp->my_env);
			tmp->my_env = ft_strdup(spli_arg[1]);
			flag = 1;
			break;
		}
		// free 2d array
		tmp = tmp->next;
	}
	if (!flag)
	{
		spli_arg = ft_split(data->cmd[1], '=');
		ft_lstadd_back(head, ft_lstnew(spli_arg[0], spli_arg[1]));
	}
	
}