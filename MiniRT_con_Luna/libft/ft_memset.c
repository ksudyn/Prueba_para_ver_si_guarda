/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:52:09 by ksudyn            #+#    #+#             */
/*   Updated: 2024/10/10 15:02:36 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int value, size_t len)
{
	size_t			i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *)str;
	while (len > i)
	{
		s[i] = (unsigned char)value;
		i++;
	}
	return (s);
}
