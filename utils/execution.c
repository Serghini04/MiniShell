/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 01:49:23 by hidriouc          #+#    #+#             */
/*   Updated: 2024/04/25 15:52:56 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	creat_pipe(int *T)
{
	if (pipe(T) == -1)
		(perror("piping probleme !!"), exit(EXIT_FAILURE));
}

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

void	run_cmd(t_mini **data)
{
	if ((*data)->fd_in == -1 || (*data)->fd_out == -1 )
		(perror("open error !!"), exit(EXIT_FAILURE));
	// if ((*data)->fd_in != 0)
	// {
	// 	dup2((*data)->fd_in, 0);
	// 	close((*data)->fd_in);
	// }
	// else
	// 	close((*data)->t_fd[0]);
	// if ((*data)->fd_out != 1)
	// {
	// 	dup2((*data)->fd_out, 1);
	// 	close((*data)->fd_out);
	// }
	// else
	// 	close ((*data)->t_fd[1]);
	if (ft_strchr((*data)->cmd[0], '/'))
		(*data)->cmd_path = (*data)->cmd[0];
	else
		(*data)->cmd_path = find_path((*data)->cmd[0], (*data)->env);
	if (!(*data)->cmd_path)
	{
		(ft_putstr_fd("bash: ", 2),ft_putstr_fd((*data)->cmd[0], 2), ft_putstr_fd(": command not found\n", 2));
		clear_t_mini(data);
		// exit(127);
		exit(EXIT_FAILURE);
	}
	if (execve((*data)->cmd_path, (*data)->cmd, (*data)->env) == -1)
	{
		(ft_putstr_fd("bash: ", 2),ft_putstr_fd((*data)->cmd[0], 2), ft_putstr_fd(": command not found\n", 2));
		clear_t_mini(data);
		exit(EXIT_FAILURE);
	}
}

void	main_process(t_mini	**data, char **env)
{
	int		pid;
	int		fdin;
	int		fdout;
	int		p_fdin;
	int		p_fdout;

	p_fdin = dup(0);
	p_fdout = dup(1);
	if((*data)->fd_in != 0)
		fdin = (*data)->fd_in;
	while (*data)
	{
		(*data)->env = env;
		if (fdin != 0)
		{
			dup2(fdin, 0);
			close(fdin);
		}
		if ((*data)->next)
		{
			creat_pipe((*data)->t_fd);
			dup2((*data)->t_fd[1], 1);
			close ((*data)->t_fd[1]);
			fdin = (*data)->t_fd[0];
		}
		else
		{
			if ((*data)->fd_in != 0)
			{
				fdin = (*data)->fd_in;
				dup2(fdin, 0);
				close(fdin);
			}
			fdout = (*data)->fd_out;
			if (fdout != 1)
			{
				dup2(fdout, 1);
				close(fdout);
			}
		}
		pid = fork();
		if (pid == 0)
		{
			run_cmd(data);
		}
		else if (pid < 0)
		{
			ft_putstr_fd("fork probleme !!", 2);
			clear_t_mini(data);
		}
		(*data) = (*data)->next;
		dup2(p_fdin, 0);
		dup2(p_fdout, 1);
	}
	while (wait(NULL) != -1)
		;
	// int c;
	// waitpid(-1, &c, 0);
	// printf("%d\n", c >> 8);
	close (p_fdin);
	close (p_fdout);
}
