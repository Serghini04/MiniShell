/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_myenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:02:34 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/23 18:20:40 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_secoure_env(t_env **head, t_env **tmp)
{
	char	*ptr;

	ptr = "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
	*tmp = ft_lstnew(ft_strjoin("PWD=", getcwd(0, 0)));
	ft_lstadd_back(head, *tmp);
	*tmp = ft_lstnew(ft_strdup("OLDPWD"));
	ft_lstadd_back(head, *tmp);
	*tmp = ft_lstnew(ft_strdup("SHLVL=1"));
	ft_lstadd_back(head, *tmp);
	*tmp = ft_lstnew(ft_strdup(ptr));
	ft_lstadd_back(head, *tmp);
	*tmp = ft_lstnew(ft_strdup("_=/usr/bin/env"));
	ft_lstadd_back(head, *tmp);
}

void	creat_myenv(t_env	**head, char **env)
{
	int		i;
	t_env	*tmp;
	int		flag;

	i = 0;
	flag = 0;
	if (!env || !(*env))
		ft_secoure_env(head, &tmp);
	else
	{
		while (env[i])
		{
			if (ft_strncmp("OLDPWD", env[i], 6))
			{
				tmp = ft_lstnew(ft_strdup(env[i]));
				ft_lstadd_back(head, tmp);
			}
			i++;
		}
	}
}
