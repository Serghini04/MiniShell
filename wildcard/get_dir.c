/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:03:33 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/20 15:06:52 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*save_find_dir(char	*name_wildcard, t_env **head)
{
	struct dirent	*ret;
	DIR				*dir;
	int				i;

	i = 0;
	if (!name_wildcard)
		return (free_t_env(head, 1), NULL);
	if (!head)
		return (free(name_wildcard), NULL);
	dir = opendir(".");
	if (!dir)
		return (perror("opendir :"), free(name_wildcard) \
										, free_t_env(head, 1), NULL);
	ret = readdir(dir);
	while (ret)
	{
		if (!ft_strncmp(ret->d_name, name_wildcard, ft_strlen(name_wildcard)))
			ft_lstadd_back(head, ft_lstnew(ft_strdup(ret->d_name)));
		ret = readdir(dir);
	}
	free(name_wildcard);
	closedir(dir);
	return (*head);
}
