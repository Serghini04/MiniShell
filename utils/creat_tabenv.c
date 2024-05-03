/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_tabenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:13:22 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/02 14:30:43 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**creat_tabenv(t_env	*head)
{
	t_env	*tmp;
	int		i;
	char	**env;
	
	tmp = head;
	i = 0;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env = (char **)malloc((i + 1) * sizeof(char*));
	if(!env)
		return(NULL);
	i = 0;
	tmp = head;
	while (tmp)
	{
		env[i] = ft_strjoin(ft_strjoin(tmp->name, "="), tmp->my_env);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return(env);
}