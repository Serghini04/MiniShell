/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:57:03 by hidriouc          #+#    #+#             */
/*   Updated: 2024/03/30 02:07:05 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	if (!*s && (char)c == 0)
		return ((char *)s);
	while (*s)
	{
		if (*s == (const char)c)
			return ((char *)s);
		s++;
	}
	if ((const char)c == '\0')
		return ((char *)s);
	return (NULL);
}
