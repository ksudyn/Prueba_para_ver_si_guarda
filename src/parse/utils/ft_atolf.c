/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atolf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:24:24 by asaiz-lo          #+#    #+#             */
/*   Updated: 2025/09/10 13:18:50 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft/libft.h"

static void	ft_skip_spaces(char *line, unsigned int *pos)
{
	while (line && line[*pos] && ft_isspace(line[*pos]))
		(*pos)++;
}

static double	get_result(char *str, unsigned int *pos)
{
	double	result;
	double	scale;
	int		decimal;

	decimal = 0;
	result = 0;
	scale = 1;
	while (ft_isdigit(str[*pos]) || str[*pos] == '.')
	{
		if (decimal)
		{
			scale /= 10;
			result += (str[*pos] - '0') * scale;
		}
		else
		{
			if (str[*pos] == '.')
				decimal++;
			else
				result = result * 10 + (str[*pos] - '0');
		}
		(*pos)++;
	}
	return (result);
}

double	ft_atolf(char *str)
{
	long double		result;
	int				sign;
	unsigned int	i;

	i = 0;
	ft_skip_spaces(str, &i);
	result = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
		sign += (str[i++] == '-') * -2;
	result = get_result(str, &i);
	return (sign * result);
}
