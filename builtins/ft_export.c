/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:57:33 by hidriouc          #+#    #+#             */
/*   Updated: 2024/06/02 10:42:26 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_input(char *name, int *flag)
{
	int	i;

	i = 1;
	while (name[i] && name[i] != '=')
	{
		if ((!(name[i] >= '_' && name[i] <= 'z') && !(name[i] >= 'A'
					&& name[i] <= 'Z') && !(name[i] >= '0' && name[i] <= '9')))
		{
			if (name[i] == '+' && name[i + 1] == '=')
				break ;
			*flag = 0;
			break ;
		}
		i++;
	}
	if (!(*flag))
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		save_exit_status(ft_strdup("1"));
		return (0);
	}
	return (1);
}

int	is_valid(char *name)
{
	int	flag;

	flag = 1;
	if (!(name[0] >= '_' && name[0] <= 'z')
		&& !(name[0] >= 'A' && name[0] <= 'Z'))
		flag = 0;
	if (name[0] == '-')
	{
		ft_putstr_fd("bash: export: `", 2);
		write(2, &name[0], 2);
		ft_putstr_fd("': invalid option\n", 2);
		save_exit_status(ft_strdup("1"));
		return (0);
	}
	else
		if (!check_input(name, &flag))
			return (0);
	return (1);
}

int	ft_change_arg(t_env *tmp, char *name, int *flag, int *i)
{
	char	*tmp1;
	char	*p;

	if (name[*i] == '+' && name[*i + 1] == '=')
	{
		tmp1 = tmp->content;
		if (!tmp->content[*i])
			p = &name[*i + 1];
		else
			p = &name[*i + 2];
		tmp->content = ft_strjoin(tmp->content, p);
		free (tmp1);
		return (*flag = 0, 0);
	}
	else if (name[*i])
	{
		free (tmp->content);
		tmp->content = ft_strdup(name);
		return (*flag = 0, 0);
	}
	else if (!name[*i] && !tmp->next)
		return (*flag = 0, 0);
	return (1);
}

int	ft_check_arg(t_env **head, t_env *tmp, char *name, int *flag)
{
	int		i;
	char	*p;

	i = 0;
	p = NULL;
	while (name[i] && tmp->content[i] && name[i]
		== tmp->content[i] && name[i] != '=')
		i++;
	if ((tmp->content[i] && tmp->content[i] == '=')
		|| (name[i] && (name[i] == '=' || name[i] == '+')))
	{
		if (!ft_change_arg(tmp, name, flag, &i))
			return (0);
	}
	else if (!name[i] && !tmp->content[i])
		*flag = 0;
	else if (!tmp->next && name[i] && ft_strchr(name, '+'))
	{
		p = ft_strchr(name, '+');
		*p = '\0';
		ft_lstadd_back(head, ft_lstnew(ft_strjoin(name, ++p)));
		*flag = 0;
		return (0);
	}
	return (1);
}

void	ft_export(char *name, t_env **head)
{
	int		flag;
	t_env	*tmp;

	if (!is_valid(name) || !head)
		return ;
	tmp = *head;
	flag = 1;
	while (tmp)
	{
		if (!ft_check_arg(head, tmp, name, &flag))
			break ;
		tmp = tmp->next;
	}
	if (flag)
	{
		ft_lstadd_back(head, ft_lstnew(ft_strdup(name)));
	}
}
