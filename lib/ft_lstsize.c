/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:37:14 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/21 10:31:13 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(t_mini	*lst)
{
	int	i;

	i = 0;
	if (lst == NULL)
		return (0);
	while (lst)
	{
		i++;
		lst = lst -> next ;
	}
	return (i);
}
