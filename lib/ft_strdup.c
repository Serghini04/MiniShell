/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:09:06 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/28 13:55:56 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s1)
{
	char	*res;
	int		len;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = ((char *)s1)[i];
		i++;
	}
	((char *)res)[i] = '\0';
	return (res);
}
