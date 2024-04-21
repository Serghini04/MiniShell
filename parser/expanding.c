/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:19:04 by meserghi          #+#    #+#             */
/*   Updated: 2024/04/12 03:43:39 by meserghi         ###   ########.fr       */
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
	int		i;
	int		v;

	i = 0;
	v = 1;
	if (str[i] >= '0' && str[i] <= '9')
	{
		v = 0;
		str++;
	}
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
	return (getenv(name_var));	
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
			res = ft_strjoin(res, ft_substr(str, s, next_doll(&str[s])));
			res = ft_strjoin(res, get_expand(&str[i + 1]));
			s = i + len_var(&str[i + 1]) + 1;
			if (str[s] == '$' && !str[s + 1])
				res = ft_strjoin(res, "$");
			else
				res = ft_strjoin(res, ft_substr(str, s, next_doll(&str[s])));
		}
		else if (str[i] == '$')
			res = ft_strjoin(res, ft_strdup("$"));
		i++;
	}
	free(str);
	if (!res || !*res)
		return (free(res), NULL);
	return (res);
}


int	expanding(t_list **head)
{
	t_list *i;
	
	i = *head;
	if (i && (i->token == t_word || i->token == t_double_q) && ft_strchr(i->wrd, '$'))
	{
		i->wrd = replace_dollar_sing(i->wrd);
		if (!i->wrd)
			return (-1);
	}
	while (i->next)
	{
		if (i->token != t_heredoc && (i->next->token == t_word || i->next->token == t_double_q))
		{
			if (ft_strchr(i->next->wrd, '$'))
			{
				i->next->wrd = replace_dollar_sing(i->next->wrd);
				if (!i->next->wrd)
					return (-1);
			}
		}
		i = i->next;
	}
	return (0);
}
