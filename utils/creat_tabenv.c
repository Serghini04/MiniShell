/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_tabenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:13:22 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/14 11:03:03 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**creat_tabenv(t_env	*head)
{
	t_env	*tmp;
	int		i;
	char	**env;
	
	if(!head)
		return (NULL);
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
		i++;
		tmp = tmp->next;
	}
	env[i] = 0;
	return(env);
}
