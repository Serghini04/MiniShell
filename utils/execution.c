/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 01:49:23 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/26 14:24:33 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(char *cmd, char **env)
{
	char	**all_paths;
	char	*path;
	int		i;
	char	*tmp;

	(1) && (i = 0, all_paths = NULL);
	while (env && env[i] && !(ft_strnstr(env[i], "PATH", 4)))
		i++;
	if (!env || !*env || !env[i])
		return (NULL);
	all_paths = ft_split(env[i] + 5, ':');
	check_malloc_sac(all_paths);
	i = 0;
	while (all_paths[i])
	{
		(1) && (path = ft_strjoin(all_paths[i], "/"), tmp = path);
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

void	ft_execut_cmd(t_mini *data)
{
	if (execve((data)->cmd_path, (data)->cmd, (data)->env) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd((data)->cmd[0], 2);
		if (ft_strchr(data->cmd[0], '/') && is_dir_or_file(data->cmd[0]) == 2)
		{
			ft_putstr_fd(": is a directory\n", 2);
			clear_t_mini(&data);
			exit(126);
		}
		else if (ft_strchr(data->cmd[0], '/') && !ft_strchr(data->cmd[1], '/')
			&& is_dir_or_file(data->cmd[0]) == -1)
			ft_putstr_fd(": No such file or directory\n", 2);
		else if (ft_strchr(data->cmd[0], '.') && ft_strchr(data->cmd[0], '/')
			&& is_dir_or_file(data->cmd[0]) == 1)
		{
			ft_putstr_fd(": Permission denied\n", 2);
			clear_t_mini(&data);
			exit(126);
		}
		else
			ft_putstr_fd(": command not found\n", 2);
		clear_t_mini(&data);
		exit(127);
	}
}

void	run_cmd(t_mini *data, t_env **env)
{
	if (!data->cmd[0])
		exit(EXIT_SUCCESS);
	if (ft_strchr((data)->cmd[0], '/'))
		(data)->cmd_path = (data)->cmd[0];
	else
		(data)->cmd_path = find_path((data)->cmd[0], (data)->env);
	if (ft_is_built_in(data))
	{
		ft_execute_buitl_in(data, env);
		return ;
	}
	else
		ft_execut_cmd(data);
}

int	ft_handel_prossid(t_mini *data, t_fd *fd, int i, t_env **lin_env)
{
	int	j;

	j = 0;
	if (fd->pid[i] == 0)
	{
		(fd->fdin != 0) && (close(fd->fdin));
		if (data->fd_in != -1 && data->fd_out != -1)
			run_cmd(data, lin_env);
		else
			exit(EXIT_FAILURE);
		(close(fd->p_fdin), close(fd->p_fdout));
		exit(EXIT_SUCCESS);
	}
	else if (fd->pid[i] < 0)
		return (close (fd->fdin), perror("fork"), red_fd_parent(fd), 0);
	return (1);
}

void	attribute_quit(struct termios save)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag = ~NOFLSH;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &save);
}

void	main_process(t_mini	*data, t_env **lin_env, struct termios *term)
{
	t_fd			fd;
	int				i;
	int				size;
	extern int		g_sig_global;
	struct termios	saver;

	tcgetattr(STDIN_FILENO, &saver);
	i = 0;
	fd.fdin = 0;
	size = ft_lstsize(data);
	data->env = creat_tabenv(*lin_env);
	if (ft_check_if_builtin(data, &fd, lin_env) && !data->next)
		return (tcsetattr(STDIN_FILENO, TCSANOW, term), red_fd_parent(&fd));
	fd.pid = malloc(size * sizeof(pid_t));
	if (!fd.pid)
		return ;
	free_arr(data->env);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	while (data)
	{
		data->env = creat_tabenv(*lin_env);
		(duping_fd(data, &fd), fd.pid[i] = fork());
		if (!ft_handel_prossid(data, &fd, i, lin_env))
			break ;
		(free_arr(data->env), red_fd_parent(&fd), data = data->next);
		i++;
	}
	signal(SIGINT, handl_sig);
	signal(SIGQUIT, SIG_IGN);
	(return_status(fd.pid, i - 1), free (fd.pid));
	if (ft_atoi(save_exit_status(NULL)) == 131)
		attribute_quit(saver);
}
