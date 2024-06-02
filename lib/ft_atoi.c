/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidriouc <hidriouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:11:48 by hidriouc          #+#    #+#             */
/*   Updated: 2024/06/02 19:28:36 by hidriouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(const char *str)
{
	long long	i_num;
	int			sign;
	size_t		i;

	i = 0;
	i_num = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((i_num >= (LLONG_MAX - (str[i] - '0')) / 10) && sign == 1)
			return (-1);
		if ((i_num > (LLONG_MAX - (str[i] - '0')) / 10) && sign == -1)
			return (-1);
		i_num = (i_num * 10) + (str[i] - '0');
		i++;
	}
	return (((int)i_num) * sign);
}

long long	advance_atoi(const char *str)
{
	long long	i_num;
	int			sign;
	size_t		i;

	i = 0;
	i_num = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((i_num > (LLONG_MAX - (str[i] - '0')) / 10) && sign == 1)
			return (-1);
		if ((i_num - 1 > (LLONG_MAX - (str[i] - '0')) / 10) && sign == -1)
			return (-1);
		i_num = (i_num * 10) + (str[i] - '0');
		i++;
	}
	return ((i_num) * sign);
}
