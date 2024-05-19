/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:53:20 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/19 15:50:29 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_dir(t_env *head)
{
	t_env *h = head;
	while (h)
	{
		printf(">>%s<<\n", h->content);
		h = h->next;
	}
}

t_env	*save_find_dir(char	*name_wildcard, t_env **head)
{
	struct dirent	*ret;
	DIR				*dir;
	int				i;

	i = 0;
	// printf("name >>%s<<\n", name_wildcard);
	if (!name_wildcard)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (perror("opendir :"), NULL);
	ret = readdir(dir);
	while (ret)
	{
		if (!ft_strncmp(ret->d_name, name_wildcard, ft_strlen(name_wildcard)))
		{
			ft_lstadd_back(head, ft_lstnew(ft_strdup(ret->d_name)));
		}
		ret = readdir(dir);
	}
	closedir(dir);
	return (*head);
}

char	*get_name_wildcard(char *line, int i)
{
	int	pos;

	pos = i;
	i--;
	while (i > 0 && !ft_isspace(line[i]) && line[i] != '*')
		i--;
	i++;
	return (ft_substr(line, i, pos - i));
}

t_env	*delete_not_find(char *name_var, t_env **head)
{
	t_env	*h;
	t_env	*new_head;

	new_head = NULL;
	if (!head || !name_var || !*head)
		return (NULL);
	h = *head;
	while (h)
	{
		if (!ft_strncmp(h->content, name_var, ft_strlen(name_var)))
			ft_lstadd_back(&new_head, ft_lstnew(h->content));
		h = h->next;
	}
	return (new_head);
}

char	*convert_lst_to_line(t_env **head)
{
	char	*res;
	t_env	*h;

	h = *head;
	res = NULL;
	while (h)
	{
		res = ft_strjoin(res, h->content);
		if (h->next)
			res =ft_strjoin(res, " ");
		h = h->next;
	}
	return (res);
}

int len_join(char *line, int i)
{
	while (i >= 0 && !ft_isspace(line[i]))
		i--;
	i++;
	return (i);
}

char	*get_expand_wildcards(char *line, int *i, int *is_first, int *s)
{
	char	*res;
	char	*name_wildcard;
	t_env	*head;

	res = NULL;
	head = NULL;
	name_wildcard = NULL;
	while (line[*i] && !ft_isspace(line[*i]))
	{
		if (line[*i] == '*')
		{
			if (*is_first)
			{
				save_find_dir(get_name_wildcard(line, *i), &head);
				*is_first = 0;
			}
			else
			{
				head = delete_not_find(get_name_wildcard(line, *i), &head);
			}

		}
		(*i)++;
	}
	if (head)
	{
		return (convert_lst_to_line(&head));
	}
	return (ft_substr(line, *s, *i));
}

char	*replace_wildcards(char *line)
{
	char	*res;
	int		is_first;
	int		i;
	int		pos;
	int		s;

	i = 0;
	s = 0;
	res = NULL;
	pos = 0;
	is_first = 1;
	while (line[i])
	{
		if (line[i] && line[i] == '*')
		{
			pos = i;
			res = ft_strjoin(res, ft_substr(line, s, len_join(line, pos)));
			res = ft_strjoin(res, get_expand_wildcards(line, &i, &is_first , &s));
			s = i;
			is_first = 1;
		}
		else
			i++;
	}
	return (res);
}


int	wildcards_part(t_list **head)
{
	t_list			*h;
	int				i;

	i = 0;
	h = *head;
	print_lst(h);
	while (h)
	{
		if (h && h->token == t_word && ft_strchr(h->wrd, '*'))
		{
			h->wrd = replace_wildcards(h->wrd);
			printf(">>%s<<\n", h->wrd);
		}
		h = h->next;
	}
	return (0);
}
