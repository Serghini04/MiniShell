/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:44:25 by meserghi          #+#    #+#             */
/*   Updated: 2024/05/18 20:35:16 by meserghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strstr(char *haystack, char *needle)
{
	int	i;
	int	j;

	i = 0;
	if (!*needle)
		return (haystack);
	while (haystack[i])
	{
		j = 0;
		while ((haystack[i + j] == needle[j]) && needle[j])
			j++;
		if (!needle[j])
			return (&haystack[i]);
		i++;
	}
	return (NULL);
}
