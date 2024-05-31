/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:59:58 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/31 11:40:53 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handelinput(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if ((!(name[i] >= '_' && name[i] <= 'z') && !(name[i] >= 'A'
					&& name[i] <= 'Z') && !(name[i] >= '0' && name[i] <= '9')))
		{
			ft_putstr_fd("bash: unset: `", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_unset(char *str, t_env	**head)
{
	t_env	*tmp;
	int		i;

	if (!head || !*head || !str || !*str || !ft_handelinput(str))
		return ;
	tmp = (*head);
	i = 0;
	while (tmp->content[i] && str[i] && tmp->content[i] == str[i])
		i++;
	if ((tmp->content[i] && !str[i] && tmp->content[i] == '='))
	{
		(*head) = (*head)->next;
		free (tmp->content);
		free (tmp);
		return ;
	}
	else if ((!tmp->content[i] && !str[i] && tmp->content[i] == str[i]))
	{
		(*head) = (*head)->next;
		free (tmp->content);
		free (tmp);
		return ;
	}
	if ((*head)->next)
		ft_unset(str, &(*head)->next);
}
