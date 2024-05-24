/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:17:19 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/24 10:06:51 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char *s, size_t start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = start;
	j = 0;
	if (!s || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		return (ft_strdup(s + start));
	if (len >= ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	res = malloc(len + 1);
	if (!res)
		return (0);
	while (j < len && s[i])
	{
		res[j] = ((char *)s)[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}
