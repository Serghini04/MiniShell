/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_t_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:05:18 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/20 15:05:48 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_t_env(t_env **env, int free_content)
{
	t_env	*h;
	t_env	*swap;

	if (!env)
		return ;
	h = *env;
	while (h)
	{
		swap = h->next;
		if (free_content)
			free(h->content);
		free(h);
		h = swap;
	}
	env = NULL;
}
