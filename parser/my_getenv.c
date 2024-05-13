/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:02:22 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/13 11:04:42 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmp_var(char *str, char *name)
{
	int	i;

	i = 0;
	if (!str || !name)
		return (0);
	while (str[i] == name[i])
		i++;
	if (!name[i] && str[i] == '=')
		return (i + 1);
	return (0);
}

char	*my_getenv(char	*name_var)
{
	t_env	*env;
	int		i;
	int		s;

	i = 0;
	env = save_env(NULL);
	if (!env)
		exit(1);
	while (env)
	{
		s = cmp_var(env->content, name_var);
		if (s)
			return (ft_substr(env->content, s, ft_strlen(env->content) - s));
		env = env->next;
	}
	return (NULL);
}
