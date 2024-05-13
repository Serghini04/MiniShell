/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_part2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:09:03 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/13 11:02:49 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_expand(char *str)
{
	char	*name_var;
	char	*res;
	int		i;
	int		v;

	(1) && (i = 0, v = 1);
	if (str[i] >= '0' && str[i] <= '9')
		(1) && (v = 0, str++);
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
	res = my_getenv(name_var);
	return (free(name_var), res);
}

char	*join_var_part_2(char *str, int *i, int *s, char *res)
{
	char	*tmp;

	*s = *i + len_var(&str[*i + 1]) + 1;
	if (str[*i + 1] == '?')
		(*s)++;
	tmp = ft_substr(str, *s, next_doll(&str[*s]));
	res = str_join(res, tmp);
	(free(tmp), tmp = NULL);
	if (!res)
		return (NULL);
	*s = -1;
	return (res);
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
	if (str[*i + 1] == '?')
		tmp = ft_strdup(save_exit_status(NULL));
	else if (!is_var(str[*i + 1]))
		tmp = ft_substr(str, *i, len_var(&str[*i + 1]) + 1);
	else
		tmp = get_expand(&str[*i + 1]);
	res = str_join(res, tmp);
	(free(tmp), tmp = NULL);
	if (!res)
		return (NULL);
	return (join_var_part_2(str, i, s, res));
}

char	*join_first_expand(char	*str, char *res, int *s)
{
	char	*tmp;

	if (!res)
	{
		*s = next_doll(str);
		tmp = ft_substr(str, 0, *s);
		if (!tmp)
			return (free(str), NULL);
		res = str_join(res, tmp);
		free(tmp);
	}
	tmp = ft_strdup("$");
	res = str_join(res, tmp);
	free(tmp);
	return (res);
}

char	*replace_dollar_sing(char *str)
{
	char	*res;
	int		s;
	int		i;

	(1) && (s = 0, i = 0, res = NULL);
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '$' || !str[i + 1]))
		{
			res = join_first_expand(str, res, &s);
		}
		else if (str[i] == '$' && (str[i + 1] || str[i + 1] == '?'))
		{
			res = join_variable(&s, str, &i, res);
			if (!res)
				return (free(str), NULL);
		}
		i++;
	}
	return (free(str), res);
}
