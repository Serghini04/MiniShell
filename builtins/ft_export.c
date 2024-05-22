/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:57:33 by hidriouc          #+#    #+#             */
/*   Updated: 2024/05/22 21:34:15 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid(char *name)
{
	int i;
	int flag;

	i = 1;
	flag = 1;
	if(!(name[0] >= '_' && name[0] <= 'z') && !(name[0] >= 'A' && name[0] <= 'Z'))
		flag = 0;
	if(name[0] == '-')
	{
		ft_putstr_fd("bash: export: `", 2);
		write(2, &name[0], 2);
		ft_putstr_fd("': invalid option\n", 2);
		return (0);
	}
	else
		while (name[i] && name[i] != '=')
		{
			if((!(name[i] >= '_' && name[i] <= 'z') && !(name[i] >= 'A' && name[i] <= 'Z') && !(name[i] >= '0' && name[i] <= '9')))
			{
				if (name[i] == '+' && name[i + 1] == '=')
					break;
				flag = 0;
				break ;
			}
			i++;
		}
	if(!flag)
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	return(1);
}
void	ft_export(char *name, t_env **head)
{
	int		i;
	int		flag;
	t_env	*tmp;
	char	*tmp1;
	char	*p;

	if(!is_valid(name))
		return ;
	tmp = *head;
	flag = 1;
	p = NULL;
	while (tmp)
	{
		i = 0;
		while (name[i] && tmp->content[i] && name[i]
			== tmp->content[i] && name[i] != '=')
			i++;
		if((tmp->content[i] && tmp->content[i] == '=') || (name[i] && name[i] == '='))
		{
			if(name[i] == '+' && name[i + 1] == '=')
			{
				tmp1 = tmp->content;
				tmp->content =ft_strjoin(tmp->content, &name[i + 2]);
				free (tmp1);
				flag = 0;
				break;
			}
			else if(name[i])
			{
				free (tmp->content);
				tmp->content = ft_strdup(name);
				flag = 0;
				break ;
			}
			else if (!name[i] && !tmp->next)
			{
				flag = 0;
				break ;
			}
		}
		else if (!name[i] && !tmp->content[i])
			flag = 0;
		else if(!tmp->next && name[i] && ft_strchr(name, '+'))
		{
			p = ft_strchr(name, '+');
			*p ='\0';
			ft_lstadd_back(head, ft_lstnew(ft_strjoin(name, ++p)));
			flag = 0;
			break;
		}
		tmp = tmp->next;
	}
	if (flag)
		ft_lstadd_back(head, ft_lstnew(ft_strdup(name)));
}
