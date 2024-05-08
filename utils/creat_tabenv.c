/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_tabenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:13:22 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/06 09:59:11 by hidriouc         ###   ########.fr       */
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
	env = malloc((i + 1) * sizeof(char*));
	if(!env)
		return(NULL);
	i = 0;
	tmp = head;
	while (tmp)
	{
		env[i] = ft_strdup(tmp->content);
		// printf("[%d]{%s}\n", i, env[i]);
		i++;
		tmp = tmp->next;
	}
	env[i] = 0;
	return(env);
}
