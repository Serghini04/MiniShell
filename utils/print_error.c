/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:35:14 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/05 12:56:24 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(t_list **head, t_list *i)
{
	if (i->token == t_pipe)
		printf("bash : syntax error near unexpected token `|'\n");
	else if (is_red(i))
		printf("bash : syntax error near unexpected token `%s'\n", i->wrd);
	save_exit_status(ft_strdup("258"));
	clear_lst(head);
}

t_free	*get_free(t_free *data)
{
	static t_free	*save_data;

	if (!data)
		return (save_data);
	save_data = data;
	return (save_data);
}

void	if_failing(void)
{
	t_free	*data;

	data = get_free(NULL);
	if (data->head)
		clear_lst(data->head);
	if (data->mini)
		clear_t_mini(data->mini);
	if (data->res)
		free(data->res);
}
