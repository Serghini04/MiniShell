/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:17:26 by hidriouc          #+#    #+#             */
/*   Updated: 2024/03/30 00:50:22 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			(free_all(all_paths), perror("allocation ERR"), exit(EXIT_FAILURE));
		if (access(path, F_OK | X_OK) == 0)
			return (free_all(all_paths), path);
		(free(path), path = NULL, i++);
	}
	return (free_all(all_paths), NULL);
}

void	run_cmd(char **av, char **env, int *t_fd)
{
	char	**cmd;
	char	*cmd_path;
	int		fd_ou;

	fd_ou = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_ou == -1)
		(perror("open error !!"), exit(EXIT_FAILURE));
	dup2(t_fd[0], 0);
	dup2(fd_ou, 1);
	close(t_fd[1]);
	close(t_fd[0]);
	close(fd_ou);
	cmd = ft_split(av[3], ' ');
	if (!cmd || !*cmd)
		(perror("command not found"), exit(EXIT_FAILURE));
	if (ft_strchr(cmd[0], '/'))
		cmd_path = cmd[0];
	else
		cmd_path = find_path(cmd[0], env);
	if (!cmd_path || (execve(cmd_path, cmd, env)) == -1)
	{
		free_all(cmd);
		free(cmd_path);
		(perror("command not found "), exit(EXIT_FAILURE));
	}
}

void	new_process(char **av, char **env, int *t_fd)
{
	char	**cmd;
	char	*cmd_path;
	int		fd_in;

	fd_in = open(av[1], O_RDONLY);
	if (fd_in == -1)
		(perror("open error !!"), exit(EXIT_FAILURE));
	if (dup2(t_fd[1], 1) == -1)
		(perror("dup2 Error !!"), exit(EXIT_FAILURE));
	if (dup2(fd_in, 0) == -1)
		(perror("dup2 Error !!"), exit(EXIT_FAILURE));
	(close(t_fd[0]), close(t_fd[1]));
	close(fd_in);
	cmd = ft_split(av[2], ' ');
	if (!cmd || !*cmd)
		(perror("bad command !!"), exit(EXIT_FAILURE));
	if (ft_strchr(cmd[0], '/'))
		cmd_path = cmd[0];
	else
		cmd_path = find_path(cmd[0], env);
	if (!(cmd_path) || execve(cmd_path, cmd, env) == -1)
	{
		(free_all(cmd), free(cmd_path));
		(perror("command not found :"), exit(EXIT_FAILURE));
	}
}

void	main_process(t_mini	*data)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		run_cmd(data->cmd, dataenv, t_fd);
	}
	else if (pid > 0)
	{
		close(t_fd[1]);
		close(t_fd[0]);
	}
	else
		(perror("fork probleme !!"), exit(EXIT_FAILURE));
}

