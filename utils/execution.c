/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 01:49:23 by hidriouc          #+#    #+#             */
/*   Updated: 2024/04/26 15:01:48 by hidriouc         ###   ########.fr       */
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
	if (ft_strchr((*data)->cmd[0], '/'))
		(*data)->cmd_path = (*data)->cmd[0];
	else
		(*data)->cmd_path = find_path((*data)->cmd[0], (*data)->env);
	if (!(*data)->cmd_path)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd((*data)->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		clear_t_mini(data);
		exit(EXIT_FAILURE);
	}
	if (execve((*data)->cmd_path, (*data)->cmd, (*data)->env) == -1)
	{
		clear_t_mini(data);
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd((*data)->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	main_process(t_mini	**data, char **env)
{
	int		pid;
	t_fd	fd;

	fd.fdin = 0;
	fd.fdout = 1;
	while (*data)
	{
		(*data)->env = env;
		duping_fd(*data, &fd);
		pid = fork();
		if (pid == 0)
		{
			if(fd.fdin != 0 )
				close(fd.fdin);
			if ((*data)->fd_in != -1)
				run_cmd(data);
			else
				exit(1);
			close(fd.p_fdin);
			close(fd.p_fdout);
		}
		else if (pid < 0)
		{
			ft_putstr_fd("fork probleme !!", 2);
			clear_t_mini(data);
		}
		
		dup2(fd.p_fdout, 1);
		close (fd.p_fdout);
		dup2(fd.p_fdin, 0);
		close (fd.p_fdin);
		(*data) = (*data)->next;
	}
	while (wait(NULL) != -1)
		;
	}
