/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_tabenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:13:22 by hidriouc          #+#    #+#             */
/*   Updated: 2024/06/02 22:24:35 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**creat_tabenv(t_env *head)
{
	t_env	*tmp;
	int		i;
	char	**env;

	tmp = head;
	i = 0;
	if (!head)
		return (NULL);
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env = malloc((i + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	tmp = head;
	while (tmp)
	{
		if (ft_strchr(tmp->content, '='))
			env[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	return (env[i] = NULL, env);
}
