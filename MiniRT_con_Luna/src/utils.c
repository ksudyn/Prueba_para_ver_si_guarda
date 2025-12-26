/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:54:50 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/26 15:29:28 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_arg(char **arg)
{
	int		i;

	if (!arg)
		return ;
	i = 0;
	while (arg && arg[i])
	{
		free(arg[i]);
		i++;
	}
	if (arg)
		free(arg);
}

int	ft_arr_len(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static double	get_fraction(char *str)
{
	double	result;
	double	div;

	result = 0.0;
	div = 10.0;
	while (*str && *str >= '0' && *str <= '9')
	{
		result += (*str - '0') / div;
		div *= 10.0;
		str++;
	}
	return (result);
}

double	ft_atolf(char *str)
{
	double	result;
	int		sign;

	result = 0.0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
		result += get_fraction(++str);
	return (result * sign);
}
