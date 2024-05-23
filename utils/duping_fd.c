/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duping_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:56:54 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/23 17:17:14 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	creat_pipe(int *T)
{
	if (pipe(T) == -1)
		(perror("piping probleme !!"), exit(EXIT_FAILURE));
}

void	red_fd_parent(t_fd *fd)
{
	if (dup2(fd->p_fdout, 1) == -1)
		(perror("dup2 Error !!"), exit(EXIT_FAILURE));
	close (fd->p_fdout);
	if (dup2(fd->p_fdin, 0) == -1)
		(perror("dup2 Error !!"), exit(EXIT_FAILURE));
	close (fd->p_fdin);
}

int	is_dir_or_file(char *name)
{
	struct stat	st;

	if (!stat(name, &st))
	{
		if (S_ISREG(st.st_mode))
			return (1);
		if (S_ISDIR(st.st_mode))
			return (2);
		return (0);
	}
	return (-1);
}

void	duping_fd(t_mini *data, t_fd *fd)
{
	fd->p_fdin = dup(0);
	fd->p_fdout = dup(1);
	if ((data)->fd_in == -1 || (data)->fd_out == -1)
		return (ft_putstr_fd("bash: No such file or directory\n", 2));
	if (data->fd_in > 0 || fd->fdin > 0)
	{
		if (data->fd_in > 1)
		{
			close(fd->fdin);
			fd->fdin = data->fd_in;
		}
		(dup2(fd->fdin, 0), close(fd->fdin));
	}
	if (data->next)
	{
		creat_pipe((fd)->t_fd);
		dup2(fd->t_fd[1], 1);
		close (fd->t_fd[1]);
		fd->fdin = fd->t_fd[0];
	}
	if (data->fd_out > 1)
	{
		dup2(data->fd_out, 1);
		close(data->fd_out);
	}
}
