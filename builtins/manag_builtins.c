/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manag_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:52:09 by hidriouc          #+#    #+#             */
/*   Updated: 2024/06/02 10:41:26 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_deslpay(t_env *tmp, char *ptr_c, int *nb)
{
	int		j;
	int		flag;

	while (tmp)
	{
		j = 0;
		flag = 0;
		if (tmp->content[0] == *ptr_c)
		{
			ft_putstr_fd("declare -x ", 1);
			while (tmp->content[j])
			{
				write(1, &tmp->content[j], 1);
				if (tmp->content[j] == '=' && !flag)
					((flag = 1) && write(1, "\"", 1));
				((!tmp->content[j + 1] && flag) && write(1, "\"", 1));
				((!tmp->content[j + 1]) && write(1, "\n", 1));
				j++;
			}
			(*nb)--;
		}
		tmp = tmp->next;
	}
}

void	sort_env(t_env *env)
{
	t_env	*tmp;
	int		i;
	char	c;

	i = 0;
	tmp = env;
	c = 'A';
	if (!env)
		return ;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	while (i > 0)
	{
		tmp = env;
		ft_deslpay(tmp, &c, &i);
		c++;
	}
}

void	ft_execute_buitl_in(t_mini *data, t_env **env, int flag)
{
	int		i;
	char	*ptr;

	i = 1;
	ptr = ft_tolower(ft_strdup(data->cmd[0]));
	(env && !ft_strcmp(ptr, "cd") && ft_cd(data, *env));
	if (!ft_strcmp(ptr, "export"))
	{
		while (data->cmd[i])
			ft_export(data->cmd[i++], env);
		if (!data->cmd[1] && data->env)
			sort_env(*env);
	}
	else if (!ft_strcmp(ptr, "pwd"))
		ft_pwd(data->env);
	else if (!ft_strcmp(ptr, "exit"))
		ft_exit(data, data->cmd[1], flag);
	else if (!ft_strcmp(ptr, "echo"))
		ft_echo(data);
	else if (!ft_strcmp(ptr, "env") && !data->cmd[1])
		ft_env(data->env);
	else if (!ft_strcmp(data->cmd[0], "unset"))
		while (data->cmd[i])
			ft_unset(data->cmd[i++], env);
	free (ptr);
}

int	ft_is_built_in(t_mini *data)
{
	char	*ptr;

	if (!data || !data->cmd[0])
		return (0);
	ptr = ft_tolower(ft_strdup(data->cmd[0]));
	if (!ft_strcmp(ptr, "cd"))
		return (free(ptr), 1);
	else if (!ft_strcmp(ptr, "pwd"))
		return (free(ptr), 1);
	else if (!ft_strcmp(data->cmd[0], "unset"))
		return (free(ptr), 1);
	else if (!ft_strcmp(ptr, "exit"))
		return (free(ptr), 1);
	else if (!ft_strcmp(ptr, "env"))
	{
		if (data->cmd[1])
			ft_putstr_fd("'env' without argumments please !! \n", 2);
		return (free(ptr), 1);
	}
	else if (!ft_strcmp(ptr, "export"))
		return (free(ptr), 1);
	else if (!ft_strcmp(data->cmd[0], "echo"))
		return (free(ptr), 1);
	return (free(ptr), 0);
}

int	ft_check_if_builtin(t_mini *data, t_fd *fd, t_env **env)
{
	if (!data && !data->cmd[0])
		return (0);
	if (data->next == NULL && ft_is_built_in(data))
	{
		if (duping_fd(data, fd))
			ft_execute_buitl_in(data, env, 1);
		if (data->env)
			free_arr(data->env);
		return (1);
	}
	return (0);
}
