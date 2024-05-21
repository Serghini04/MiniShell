/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:07:09 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/21 10:31:53 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_cmd(t_list **head)
{
	t_list	*i;
	char	**cmd;

	i = *head;
	while (i)
	{
		if (i->token == t_word && find_space(i->wrd))
		{
			cmd = my_split(i->wrd);
			if (!cmd)
				return (-1);
			add_split_lst(cmd, &i, head);
		}
		else
			i = i->next;
	}
	return (0);
}
