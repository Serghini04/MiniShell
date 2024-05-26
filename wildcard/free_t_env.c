/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_t_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:05:18 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/26 14:56:01 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clearlist_env(t_env **head)
{
	t_env	*tmp;
	t_env	*swap;

	tmp = *head;
	while (tmp)
	{
		swap = tmp->next;
		free(tmp->content);
		free(tmp);
		tmp = swap;
	}
	*head = NULL;
}
int	need_to_exp_wildards(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (0);
		i++;
	}
	return (1);
}

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
