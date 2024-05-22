/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:59:58 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/22 21:34:28 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(char *str, t_env	**head)
{
	t_env	*tmp;
	int		i;
	
	if (!head || !*head || !str || !*str)
		return ;
	tmp = (*head);
	i = 0;
	while (tmp->content[i] && str[i] && tmp->content[i] == str[i])
		i++;
	if((tmp->content[i] && str[i] == '\0' && tmp->content[i] == '='))
	{
		(*head) = (*head)->next;
		return ;
	}
	else if ((!tmp->content[i] && !str[i] && tmp->content[i] == str[i]))
	{
		(*head) = (*head)->next;
		return ;
	}
	if((*head)->next)
		ft_unset(str, &(*head)->next);
}
