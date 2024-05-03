/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 08:57:17 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/03 09:25:08 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_mini *data)
{
	t_env	*env;
	int		i;
	
	env = data->head;
	i = 0;
	while(ft_strcmp(env->name, "PWD"))
		env = env->next;
	ft_putstr_fd(env->my_env, 1);
	ft_putstr_fd("\n", 1);
}