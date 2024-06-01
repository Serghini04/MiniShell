/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:51:42 by hidriouc          #+#    #+#             */
/*   Updated: 2024/06/01 17:14:31 by hidriouc         ###   ########.fr       */
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

void	up_pwd_oldpwd(char *tmp, t_env **head, char *old_path)
{
	char	*oldpwd;
	char	*pwd;

	pwd = ft_strjoin("PWD=", tmp);
	ft_export(pwd, head);
	free(pwd);
	if (old_path)
	{
		oldpwd = ft_strjoin("OLDPWD=", old_path);
		ft_export(oldpwd, head);
		free(oldpwd);
	}
	save_exit_status(ft_strdup("0"));
}

void	ft_changedir(char *new_path, char	*old_path, t_env **head)
{
	char		*tmp;
	char		*pwd;

	tmp = NULL;
	if (chdir(new_path) == 0)
	{
		tmp = getcwd(NULL, 0);
		if (!tmp)
		{
			pwd = ft_strjoin("PWD+=", "/..");
			ft_export(pwd, head);
			free(pwd);
			ft_putstr_fd("bash: cd: ..: Previous directory not exist\n", 2);
			save_exit_status(ft_strdup("0"));
		}
		else
			up_pwd_oldpwd(tmp, head, old_path);
	}
	else
		perror("chdir");
	free(tmp);
}

void	ft_chek(t_mini *data, char *new_path, char *old_path, t_env *head)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (data->env && data->env[i])
	{
		if (ft_strncmp(data->env[i], "HOME=", 5) == 0 || data->cmd[1])
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag)
		ft_changedir(new_path, old_path, &head);
	else
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		save_exit_status(ft_strdup("1"));
	}
	free(old_path);
}

int	ft_cd(t_mini *data, t_env *env)
{
	char	*new_path;
	int		i;
	char	*old_path;
	t_env	*head;

	head = env;
	i = 0;
	new_path = NULL;
	old_path = getcwd(NULL, 0);
	if (data->cmd[1])
		new_path = ft_strdup(data->cmd[1]);
	else
		new_path = ft_strdup(getenv("HOME"));
	if (data->cmd[1] && access(new_path, F_OK) != 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(new_path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		save_exit_status(ft_strdup("1"));
		return (free(new_path), free(old_path), 1);
	}
	else
		ft_chek(data, new_path, old_path, env);
	free(new_path);
	return (1);
}
