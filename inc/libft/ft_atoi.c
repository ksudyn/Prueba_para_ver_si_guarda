/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:02:04 by alvaro            #+#    #+#             */
/*   Updated: 2025/11/06 12:09:54 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char *str)
{
	size_t	i;
	long	nbr;

	nbr = 0;
	i = 0;
	while (*str == ' ' || ('\t' <= *str && *str <= '\r'))
		str++;
	if (str)
	{
		if (str[0] == '+' || str[0] == ' ' || str[0] == '-')
			i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			nbr *= 10;
			nbr += (str[i] - 48);
			if (nbr > INT_MAX && str[0] != '-')
				return (INT_MAX);
			if (str[0] == '-' && (nbr * -1) < INT_MIN)
				return (INT_MIN);
			i++;
		}
		nbr *= ((str[0] != '-') - (str[0] == '-'));
	}
	return ((int)nbr);
}
/*
int	main(int ac, char *av[])
{

	printf("mio = %d\nel weno = %d \n diff = %d", ft_atoi(av[1]), atoi(av[1]),
		ft_atoi(av[1])-atoi(av[1]));

	return (0);
}*/
