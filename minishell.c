/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:23:39 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/21 01:43:12 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void f()
{
	system("leaks minishell");
}

int main()
{
	char *res;

	while (1)
	{
		res = readline("hi me>> ");
		if (!res)
		{
			free(res);
			break;
		}
		if (*res)
			add_history(res);
		parsing_part(res);
	}
	atexit(f);
	return (0);
}