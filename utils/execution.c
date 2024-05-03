/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 01:49:23 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/03 13:17:35 by hidriouc         ###   ########.fr       */
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
	while (!(ft_strnstr(env[i], "PATH", 4)))
		i++;
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

void	run_cmd(t_mini *data)
{
	if (ft_strchr((data)->cmd[0], '/'))
		(data)->cmd_path = (data)->cmd[0];
	else
		(data)->cmd_path = find_path((data)->cmd[0], (data)->env);
	if (!(data)->cmd_path)
	{
		perror("cmd ");
		exit(EXIT_FAILURE);
	}
	if (execve((data)->cmd_path, (data)->cmd, (data)->env) == -1)
	{
		clear_t_mini(&data);
		perror("execve ");
		exit(EXIT_FAILURE);
	}
}

void	ft_execute_buitl_in(t_mini *data)
{
	if (data->fd_in != 0)
	{
		dup2(data->fd_in, 0);
		close(data->fd_in);
	}
	if (data->fd_out != 1)
	{
		dup2(data->fd_out, 1);
		close(data->fd_out);
	}
	if (!ft_strcmp(data->cmd[0], "cd"))
		ft_cd(data);
	else if (!ft_strcmp(data->cmd[0], "export"))
		ft_export( &(data->head),data);
	else if (!ft_strcmp(data->cmd[0], "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(data->cmd[0], "export"))
		ft_echo(data);
	// else if (!ft_strcmp(data->cmd[0], "export"))
	// 	ft_export( &(data->head),data);
	// else if (!ft_strcmp(data->cmd[0], "export"))
	// 	ft_export( &(data->head),data);
}

int	ft_is_built_in(char **cmd)
{
	ft_tolower(cmd[0]);
	if (!ft_strcmp(cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (1);
	// else if (!ft_strcmp(cmd[0], "unset"))
	// 	return (1);
	// else if (!ft_strcmp(cmd[0], "env"))
	// 	return (1);
	// else if (!ft_strcmp(cmd[0], "exit"))
	// 	return (1);
	else if (!ft_strcmp(cmd[0], "echo"))
		return (1);
	else
		return (0);
}

int	ft_check_if_builtin(t_mini *data)
{
	if (data && data->next == NULL && ft_is_built_in(data->cmd))
		return (ft_execute_buitl_in(data), 1);
	return (0);
}

void	main_process(t_mini	*data, char **env)
{
	t_fd	fd;

	(1) && (fd.fdin = 0, fd.fdout = 1);
	data->env = env;
	if (ft_check_if_builtin(data))
		return ;
	while (data)
	{
		(1) && (data->env = env, duping_fd(data, &fd), fd.pid = fork());
		if (fd.pid == 0)
		{
			if (fd.fdin != 0)
				close(fd.fdin);
			if ((data)->fd_in != -1 && (data)->fd_out != -1)
				run_cmd(data);
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
	while (wait(NULL) != -1)
		;
}
