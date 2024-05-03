/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:51:42 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/03 11:26:53 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_tolower(char	*str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
}

void	ft_cd(t_mini *data)
{
	char	*new_path;
	t_env	*env;
	char	*tmp;
	char	*old_path;

	env = data->head;
	old_path = getcwd(NULL, 0);
	if (data->cmd[1])
		new_path = data->cmd[1];
	else
		new_path = ft_strdup(getenv("HOME"));
	if (access(new_path, F_OK) != 0)
			perror(new_path);
	else
	{
		if (chdir(new_path) == 0)
		{
			while (ft_strcmp(env->name, "PWD"))
				env = env->next;
			tmp = getcwd(NULL, 0);
			if(!tmp)
				perror("getcwd");
			else
			{
				(free(env->my_env),free(env->next->my_env));
				env->my_env = tmp;
				env->next->my_env = old_path;
				data->env = creat_tabenv(data->head);
			}
		}
		else
			perror("chdir");
	}
}
