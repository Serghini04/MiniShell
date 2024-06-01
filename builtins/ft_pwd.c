/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 08:57:17 by hidriouc          #+#    #+#             */
/*   Updated: 2024/06/01 16:24:37 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(char **env)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putstr_fd(pwd, 1);
		free(pwd);
	}
	else
	{
		while (env[i])
		{
			if (!ft_strncmp("PWD=", env[i], 4))
				ft_putstr_fd((env[i] + 4), 1);
			i++;
		}
	}
	ft_putstr_fd("\n", 1);
}
