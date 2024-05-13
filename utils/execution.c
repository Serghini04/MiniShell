/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 01:49:23 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/13 09:36:59 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	char	*res;
	int		i;
	int		j;

	(1) && (i = 0, j = 0);
	if (!s1 && s2)
		return (s2);
	else if (!s2 && s1)
		return (s1);
	if (!s1 && !s2)
		return (ft_strdup(""));
	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

char	*find_path(char *cmd, char **env)
{
	char	**all_paths;
	char	*path;
	int		i;
	char	*tmp;

	i = 0;
	all_paths = NULL;
	while (env[i] && !(ft_strnstr(env[i], "PATH", 4)))
		i++;
	if(!env[i])
		return (NULL);
	all_paths = ft_split(env[i] + 5, ':');
	if (!all_paths || !*all_paths)
		(perror("allocation problem !!"), exit(EXIT_FAILURE));
	i = 0;
	while (all_paths[i])
	{
		path = ft_strjoin(all_paths[i], "/");
		tmp = path;
		path = ft_strjoin(path, cmd);
		free(tmp);
		if (!path)
			(free_arr(all_paths), perror("allocation ER"), exit(EXIT_FAILURE));
		if (access(path, F_OK | X_OK) == 0)
			return (free_arr(all_paths), path);
		(free(path), path = NULL, i++);
	}
	return (free_arr(all_paths), NULL);
}

static void	red_fd_parent(t_fd *fd)
{
	if (dup2(fd->p_fdout, 1) == -1)
		(perror("dup2 Error !!"), exit(EXIT_FAILURE));
	close (fd->p_fdout);
	if (dup2(fd->p_fdin, 0) == -1)
		(perror("dup2 Error !!"), exit(EXIT_FAILURE));
	close (fd->p_fdin);
}

void	run_cmd(t_mini *data, t_env *env)
{
	if (!data->cmd[0])
		exit(1);
	data->env = creat_tabenv(env);
	if (ft_strchr((data)->cmd[0], '/'))
		(data)->cmd_path = (data)->cmd[0];
	else
		(data)->cmd_path = find_path((data)->cmd[0], (data)->env);
	if (!(data)->cmd_path && !ft_is_built_in(data))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd((data)->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		clear_t_mini(&data);
		exit(127);
	}
	if (ft_is_built_in(data))
	{
		ft_export(ft_strjoin("_=", NULL), &env);
		ft_execute_buitl_in(data, env);
	}
	else if (execve((data)->cmd_path, (data)->cmd, (data)->env) == -1)
	{
		clear_t_mini(&data);
		ft_putstr_fd("bash: ", 2);
		if ((data))
			ft_putstr_fd((data)->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	exit(1);
}

void	return_status()
{
	int		ret;
	char	*res;

	while (waitpid(0, &ret, 0) != -1)
		;
	res = ft_itoa(WEXITSTATUS(ret));
	if (!res)
		return ;
	save_exit_status(res);
}
void	ft_print_fd(char *str, int fd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!str)
		return ;
	while(str[i])
	{
		write(fd, &str[i], 1);
		if (str[i] == '=')
		{
			write(fd, "\"", 1);
			flag = 1;
		}
		if (!str[i + 1] && flag)
			write(fd, "\"", 1);
		i++;
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
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	while (i > 0)
	{
		tmp = env;
		while(tmp)
		{
			if(tmp->content[0] == c)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_print_fd(tmp->content, 1);
				ft_putstr_fd("\n", 1);
				i--;
			}
			tmp = tmp->next;
		}
		c++;
	}
}

void	ft_execute_buitl_in(t_mini *data, t_env *env)
{
	int	i;

	i = 1;
	if (!ft_strcmp(data->cmd[0], "cd"))
		ft_cd(data, env);
	else if (!ft_strcmp(data->cmd[0], "export"))
	{
		if(data->cmd[1])
			while (data->cmd[i])
				ft_export(data->cmd[i++], &env);
		else
			sort_env(env);
	}
	else if (!ft_strcmp(data->cmd[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(data->cmd[0], "echo"))
		ft_echo(data);
	else if (!ft_strcmp(data->cmd[0], "env") && !data->cmd[1])
		ft_env(data->env);
	else if (!ft_strcmp(data->cmd[0], "unset"))
		while (data->cmd[i])
			ft_unset(data->cmd[i++], &env);
}

int	ft_is_built_in(t_mini *data)
{
	ft_tolower(data->cmd[0]);
	if (!ft_strcmp(data->cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(data->cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(data->cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(data->cmd[0], "env") && find_path(data->cmd[0],data->env))
		return (1);
	else if (!ft_strcmp(data->cmd[0], "export"))
		return (1);
	else if (!ft_strcmp(data->cmd[0], "echo"))
		return (1);
	else
		return (0);
}

int	ft_check_if_builtin(t_mini *data, t_fd *fd, t_env *env)
{
	if (!data && !data->cmd[0])
		return (0);
	if (data->next == NULL && ft_is_built_in(data))
		return (duping_fd(data, fd), ft_execute_buitl_in(data, env), 1);
	return (0);
}

void	main_process(t_mini	*data, t_env *strp)
{
	t_fd	fd;

	(1) && (fd.fdin = 0, fd.fdout = 1);
	data->env = creat_tabenv(strp);
	if (ft_check_if_builtin(data, &fd, strp))
	{
		red_fd_parent(&fd);
		return ;
	}
	while (data)
	{
		(1) && (duping_fd(data, &fd), fd.pid = fork());
		if (fd.pid == 0)
		{
			if (fd.fdin != 0)
				close(fd.fdin);
			if ((data)->fd_in != -1 && (data)->fd_out != -1)
				run_cmd(data, strp);
			else
				exit(EXIT_FAILURE);
			(close(fd.p_fdin), close(fd.p_fdout));
		}
		else if (fd.pid < 0)
		{
			(perror("fork"), clear_t_mini(&data), red_fd_parent(&fd));
			return ;
		}
		(red_fd_parent(&fd), data = data->next);
	}
	clear_t_mini(&data);
	return_status();
}
