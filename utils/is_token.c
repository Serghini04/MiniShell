/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:04:30 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/31 22:48:54 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_red(t_list *c)
{
	if (!c)
		return (0);
	else if (c->token == t_red_in)
		return (1);
	else if (c->token == t_red_out)
		return (1);
	else if (c->token == t_app)
		return (1);
	else if (c->token == t_heredoc)
		return (1);
	return (0);
}

int	is_q(int c)
{
	if (c == t_signle_q || c == t_double_q)
		return (1);
	return (0);
}

int	check_token(char c)
{
	if (c == '<')
		return (t_red_in);
	else if (c == '>')
		return (t_red_out);
	else if (c == '|')
		return (t_pipe);
	else if (c == '\0')
		return (t_last);
	return (-1);
}

int	find_space(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t')
			return (1);
		i++;
	}
	return (0);
}
