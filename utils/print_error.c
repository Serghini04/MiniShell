/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:35:14 by meserghi          #+#    #+#             */
/*   Updated: 2024/03/24 01:13:17 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(t_list **head, t_list *i)
{
	if (i->token == t_pipe)
		printf("bash : syntax error near unexpected token `|'\n");
	else if (is_red(i))
		printf("bash : syntax error near unexpected token `%s'\n", i->wrd);
	clear_lst(head);
}