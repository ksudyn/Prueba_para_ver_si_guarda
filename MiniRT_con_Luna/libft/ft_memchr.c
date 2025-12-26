/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:00:36 by ksudyn            #+#    #+#             */
/*   Updated: 2024/10/10 14:51:53 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t len)
{
	unsigned int	i;
	unsigned char	character;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	character = (unsigned char)c;
	while (len > i)
	{
		if (str[i] == character)
			return (i + (void *)s);
		i++;
	}
	return (NULL);
}
