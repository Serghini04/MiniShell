/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:57:18 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/31 21:25:27 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **env)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	ptr = find_path("env", env);
	if (!env || !*env || !ptr)
	{
		ft_putstr_fd("bash : env: no such file or directory\n", 2);
		save_exit_status(ft_strdup("127"));
		return ;
	}
	free(ptr);
	ptr = "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j])
			j++;
		if (ft_strcmp(env[i], ptr))
			if (ft_strchr(env[i], '='))
				(ft_putstr_fd(env[i], 1), ft_putstr_fd("\n", 1));
		save_exit_status(ft_strdup("0"));
	}
}
