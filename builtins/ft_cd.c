/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:51:42 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/24 09:24:12 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_tolower(char	*str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
	return (str);
}

void	ft_changedir(char *new_path, char	*old_path, t_env **head)
{
	char	*tmp;

	if (chdir(new_path) == 0)
	{
		tmp = getcwd(NULL, 0);
		if (!tmp)
			perror(tmp);
		else
		{
			ft_export(ft_strjoin("PWD=", tmp), head);
			ft_export(ft_strjoin("OLDPWD=", old_path), head);
		}
	}
	else
		perror("chdir");
}

void	ft_cd(t_mini *data, t_env *env)
{
	char	*new_path;
	int		i;
	char	*old_path;
	t_env	*head;

	head = env;
	i = 0;
	old_path = getcwd(NULL, 0);
	if (data->cmd[1])
		new_path = data->cmd[1];
	else
		new_path = ft_strdup(getenv("HOME"));
	if (access(new_path, F_OK) != 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(new_path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		save_exit_status("1");
		return ;
	}
	else
		ft_changedir(new_path, old_path, &head);
}
