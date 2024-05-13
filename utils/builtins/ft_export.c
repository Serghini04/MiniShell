/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:57:33 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/12 18:32:19 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	is_valid(char *name)
// {

// }
void	ft_export(char *name, t_env **head)
{
	int		i;
	int		flag;
	t_env	*tmp;
	char	*tmp1;

	// if(!is_valid(name))
	// 	return ;
	tmp = *head;
	flag = 1;
	while (tmp)
	{
		i = 0;
		while (name[i] && tmp->content[i] && name[i]
			== tmp->content[i] && name[i] != '=')
			i++;
		if(tmp->content[i] == '=')
		{
			if(name[i] == '+' && name[i + 1] == '=')
			{
				tmp1 = tmp->content;
				tmp->content =ft_strjoin(tmp->content, &name[i + 2]);
				flag = 0;
				free (tmp1);
			}
			else
			{
				free (tmp->content);
				tmp->content = ft_strdup(name);
				flag = 0;
				return ;
			}
		}
		tmp = tmp->next;
	}
	if (flag)
		ft_lstadd_back(head, ft_lstnew(ft_strdup(name)));

}
