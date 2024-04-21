/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 01:49:23 by hidriouc          #+#    #+#             */
/*   Updated: 2024/04/20 19:51:55 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	creat_pipe(int *T)
{
	if (pipe(T) == -1)
		(perror("piping probleme !!"), exit(EXIT_FAILURE));
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

void	run_cmd(t_mini **data)
{
	if ((*data)->fd_in == -1 || (*data)->fd_out == -1 )
		(perror("open error !!"), exit(EXIT_FAILURE));
	if ((*data)->fd_in != 0)
	{
		dup2((*data)->fd_in, 0);
		close((*data)->fd_in);
	}
	if ((*data)->fd_out != 1)
	{
		dup2((*data)->fd_out, 1);
		close((*data)->fd_out);
	}
	if (ft_strchr((*data)->cmd[0], '/'))
		(*data)->cmd_path = (*data)->cmd[0];
	else
		(*data)->cmd_path = find_path((*data)->cmd[0], (*data)->env);
	if (!(*data)->cmd_path)
	{
		(ft_putstr_fd("bash: ", 2),ft_putstr_fd((*data)->cmd[0], 2), ft_putstr_fd(": command not found\n", 2));
		clear_t_mini(data);
		exit(EXIT_FAILURE);
	}
	if (execve((*data)->cmd_path, (*data)->cmd, (*data)->env) == -1)
	{
		clear_t_mini(data);
		(ft_putstr_fd("bash: ", 2), ft_putstr_fd(": command not found\n", 2));
		exit(EXIT_FAILURE);
	}
}

void	main_process(t_mini	**data, char **env)
{
	int		pid;
	int		t_fd[2];
	int		swp_fd_out1;
	int		swp_fd_in;
	t_mini		*tmp;

	tmp = *data;
	swp_fd_in = (*data)->fd_in;
	while (tmp->next)
		tmp = tmp->next;
	swp_fd_out1 = tmp->fd_out;
	while (*data)
	{
		(*data)->env = env;
		if ((*data)->next)
		{
			creat_pipe(t_fd);
			(*data)->fd_in = swp_fd_in;
			if ((*data)->fd_out == 1)
				(*data)->fd_out = t_fd[1];
			else
				close(t_fd[1]);
			swp_fd_in = t_fd[0];
		}
		else
		{
			(*data)->fd_in = swp_fd_in;
			(*data)->fd_out = swp_fd_out1;
		}
		pid = fork();
		if (pid == 0)
		{
			run_cmd(data);
		}
		else if (pid > 0)
		{
			close(t_fd[0]);
			close(t_fd[1]);
			if ((*data)->next)
			{
				close((*data)->fd_in);
				close((*data)->fd_out);
			}
		}
		else
		{
			ft_putstr_fd("fork probleme !!", 2);
			clear_t_mini(data);
		}
		(*data) = (*data)->next;
	}
	while (wait(NULL) != -1)
		;
}
