/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:59:58 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/07 10:03:45 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(char *str, t_env	**head)
{
	t_env	*tmp;
	int		i;
	
	if (!head || !*head)
		return ;
	tmp = (*head);
	if (tmp)
	{
		i = 0;
		while (tmp->content[i] && str[i] && tmp->content[i] == str[i])
		{
			if(tmp->content[i + 1] && tmp->content[i + 1] == '=' && str[i + 1] == '\0')
			{
				*head = tmp->next;
				return ;
			}
			i++;
		}
		tmp = tmp->next;
	}
	if(!(*head)->next)
	{
		ft_putstr_fd("bash: unset: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return ;
	}
	ft_unset(str, &(*head)->next);
}
