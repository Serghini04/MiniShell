/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:19:04 by meserghi          #+#    #+#             */
/*   Updated: 2024/04/22 17:13:41 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// you need to fix >>$

char	*find_dollar_sing(char *str)
{
	char	*res;
	int		len;
	int		i;

	if (!str || !*str)
		return (str);
	len = ft_strlen(str) - 1;
	i = 0;
	if ((len > 0 && str[len - 1] == '$') || str[len] != '$')
		return (str);
	res = malloc(len + 1);
	if (!res)
		return (free(str), NULL);
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (free(str), res);
}

int	remove_dollar_sign(t_list **head)
{
	t_list	*h;

	if (!head)
		return (0);
	h = *head;
	while (h->next)
	{
		if (is_q(h->next->token))
		{
			h->wrd = find_dollar_sing(h->wrd);
			if (!h->wrd)
				return (-1);
		}
		h = h->next;
	}
	return (0);
}

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
		res = ft_strjoin(res, tmp);
		if (!res)
			return (NULL);
	}
	tmp = get_expand(&str[*i + 1]);
	res = ft_strjoin(res, tmp);
	(free(tmp), tmp = NULL);
	if (!res)
		return (NULL);
	*s = *i + len_var(&str[*i + 1]) + 1;
	tmp = ft_substr(str, *s, next_doll(&str[*s]));
	res = ft_strjoin(res, tmp);
	(free(tmp), tmp = NULL);
	if (!res)
		return (NULL);
	*s = -1;
	return (res);
}

char	*replace_dollar_sing(char *str)
{
	char	*res;
	int		s;
	int		i;

	s = 0;
	i = 0;
	res = NULL;
	while (str[i])
	{
		if (str[i + 1] && str[i] == '$')
		{
			res = join_variable(&s, str, &i, res);
			if (!res)
				return (NULL);
		}
		else if (str[i] == '$')
			res = ft_strjoin(res, ft_strdup("$"));
		i++;
	}
	if (!res || !*res)
		return (free(str), free(res), NULL);
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

	i = *head;
	if (!i)
		return (0);
	if (is_expand(i->token, 0) && ft_strchr(i->wrd, '$'))
	{
		i->wrd = replace_dollar_sing(i->wrd);
		if (!i->wrd)
			return (clear_lst(head), -1);
	}
	while (i->next)
	{
		if (i->token != t_heredoc && is_expand(i->next->token, 0))
		{
			if (ft_strchr(i->next->wrd, '$'))
			{
				i->next->wrd = replace_dollar_sing(i->next->wrd);
				if (!i->next->wrd)
					return (clear_lst(head), -1);
			}
		}
		i = i->next;
	}
	return (0);
}
