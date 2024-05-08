/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_myenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:02:34 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/07 15:05:31 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	creat_myenv(t_env	**head, char **env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	if (!(*env))
	{
		tmp = ft_lstnew(ft_strjoin("PWD=", getcwd(0, 0)));
		ft_lstadd_back(head, tmp);
	}
	else
	{
		while(env[i])
		{
			tmp = ft_lstnew(ft_strdup(env[i]));
			ft_lstadd_back(head, tmp);
			i++;
		}
	}
}
