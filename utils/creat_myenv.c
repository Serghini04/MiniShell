/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_myenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:02:34 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/02 14:04:57 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	creat_myenv(t_env	**head, char **env)
{
	int		i;
	t_env	*tmp;
	char	**tb;

	i = 0;
	while(env[i])
	{
		tb = ft_split(env[i], '=');
		tmp = ft_lstnew(tb[0], tb[1]);
		ft_lstadd_back(head, tmp);
		i++;
	}
}
