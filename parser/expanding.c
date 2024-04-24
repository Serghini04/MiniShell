/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:19:04 by meserghi          #+#    #+#             */
/*   Updated: 2024/04/24 21:40:12 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_var(int c)
{
	if (c == '_' || (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

char	*get_expand(char *str)
{
	char	*name_var;
	char	*res;
	int		i;
	int		v;

	(1) && (i = 0, v = 1);
	if (str[i] >= '0' && str[i] <= '9')
		(v = 0, str++);
	while (str[i] && is_var(str[i]))
		i++;
	name_var = malloc(i + 1);
	if (!name_var)
		return (NULL);
	i = 0;
	while (str[i] && is_var(str[i]))
	{
		name_var[i] = str[i];
		i++;
	}
	name_var[i] = '\0';
	if (!v)
		return (name_var);
	res = getenv(name_var);
	return (free(name_var), ft_strdup(res));
}

int	next_doll(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

int	len_var(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && is_var(str[i]))
		i++;
	return (i);
}

int	count_doll(char *str)
{
	int	i;
	int c;

	c = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i + 1] && str[i] == '$')
			c++;
		i++;
	}
	return (c);
}

char	*join_variable(int *s, char *str, int *i, char *res)
{
	char	*tmp;

	if (*s != -1)
	{
		tmp = ft_substr(str, *s, next_doll(&str[*s]));
		res = str_join(res, tmp);
		(free(tmp), tmp = NULL);
		if (!res)
			return (NULL);
	}
	tmp = get_expand(&str[*i + 1]);
	res = str_join(res, tmp);
	(free(tmp), tmp = NULL);
	if (!res)
		return (NULL);
	*s = *i + len_var(&str[*i + 1]) + 1;
	tmp = ft_substr(str, *s, next_doll(&str[*s]));
	res = str_join(res, tmp);
	(free(tmp), tmp = NULL);
	if (!res)
		return (NULL);
	*s = -1;
	return (res);
}

char	*replace_dollar_sing(char *str)
{
	char	*res;
	char	*tmp;
	int		s;
	int		i;

	(1) && (s = 0, i = 0, res = NULL);
	while (str[i])
	{
		if (str[i + 1] && str[i + 1] != '$' && str[i] == '$')
		{
			res = join_variable(&s, str, &i, res);
			if (!res)
				return (NULL);
		}
		else if (str[i] == '$' && (!str[i + 1] || str[i + 1] == '$'))
		{
			if (!res)
			{
				tmp = ft_substr(str, 0, next_doll(str));
				res = str_join(res, tmp);
				(free(tmp), tmp = NULL);
			}
			(tmp = ft_strdup("$"), res = str_join(res, tmp));
			free(tmp);
		}
		i++;
	}
	if (!res)
		return (free(str), NULL);
	return (free(str), res);
}

int	is_expand(int token, int heredoc)
{
	if (token == t_word || (token == t_double_q && !heredoc))
		return (1);
	return (0);
}

int	expanding(t_list **head)
{
	t_list *i;
	// int		v;

	i = *head;
	if (!i)
		return (0);
	if (is_expand(i->token, 0) && ft_strchr(i->wrd, '$'))
	{
		i->wrd = replace_dollar_sing(i->wrd);
		if (!i->wrd)
			return (clear_lst(head), -1);
		else if (!*i->wrd)
			return (free(i->wrd), free(i), *head = NULL, 0);
	}
	print_lst(*head);
	while (i && i->next)
	{
		// v = 0;
		if (i->token != t_heredoc && is_expand(i->next->token, 0))
		{
			if (ft_strchr(i->next->wrd, '$'))
			{
				i->next->wrd = replace_dollar_sing(i->next->wrd);
				if (!i->next->wrd)
					return (clear_lst(head), -1);
				else if (!*i->next->wrd)
				{
					delete_node(i->next);
					print_lst(*head);
					// continue;
				}
			}
		}
		// if (!v)
		i = i->next;
	}
	return (0);
}
