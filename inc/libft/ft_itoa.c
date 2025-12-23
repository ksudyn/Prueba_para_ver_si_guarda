/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 20:48:32 by alvaro            #+#    #+#             */
/*   Updated: 2024/03/20 18:10:31 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//#include <stdio.h>
//#include <stdlib.h>
//
// void	*ft_calloc(size_t count, size_t size)
//{
//	char	*ptr;
//	size_t	i;
//
//	ptr = malloc(count * size);
//	if (ptr == NULL)
//	{
//		free(ptr);
//		return (NULL);
//	}
//	if (ptr != NULL)
//	{
//		i = 0;
//		while (i < count * size)
//		{
//			ptr[i] = 0;
//			i++;
//		}
//	}
//	return (ptr);
//}

char	*mem_alloc(long nbr, int len)
{
	if (nbr == 0)
		return (ft_calloc(2, sizeof(char)));
	return (ft_calloc(len, sizeof(char)));
}

int	get_len(long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	long	nbr;

	nbr = (long)n;
	len = get_len(nbr);
	result = mem_alloc(nbr, 1 + len);
	if (result == NULL)
		return (free(result), NULL);
	result[len--] = '\0';
	if (nbr == 0)
		result[0] = '0';
	else if (nbr < 0)
	{
		result[0] = '-';
		nbr *= -1;
	}
	while (nbr > 0 && len >= 0)
	{
		result[len--] = (char)('0' + nbr % 10);
		nbr /= 10;
	}
	return (result);
}

// int main(int ac, char *av[])
//{
//    char *s = ft_itoa(9);
//    //int s2 = itoa(atoi(av[1]));
//    //printf("Mio = %s\nExpected = %s",s, av[1]);
//    printf("%s", s);
//
//    return (0);
//}