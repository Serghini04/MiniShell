/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duping_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:56:54 by hidriouc          #+#    #+#             */
/*   Updated: 2024/03/31 01:59:44 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	duping_fd(t_mini *data, int *t_fd)
{
	if (data->flag == 0)
	{
		if ((*data)->fd_out != -1)
		{
			if (dup2(data->fd_out, t_fd[1]) == -1)
				(perror("piping probleme !!"), exit(EXIT_FAILURE));
		}
		else
		{
			perror("piping probleme !!");
			exit(EXIT_FAILURE);
		}
	}
	else if ((*data)->flag == 1)
	{
		if (dup2(data->fd_in, t_fd[0]) == -1)
			(perror("piping probleme !!"), exit(EXIT_FAILURE));
		if (dup2(data->fd_out, t_fd[1]) == -1)
			(perror("piping probleme !!"), exit(EXIT_FAILURE));
	}
	else
	{
		if (dup2((*data)->fd_in,t_fd[0]) == -1)
			(perror("piping probleme !!"), exit(EXIT_FAILURE));
	}
	(close(t_fd[1]), close(t_fd[0]));
}
