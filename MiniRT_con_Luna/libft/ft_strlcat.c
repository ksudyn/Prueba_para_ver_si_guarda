/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:18:19 by ksudyn            #+#    #+#             */
/*   Updated: 2024/10/10 15:04:29 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *str, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = ft_strlen (str);
	j = ft_strlen (dest);
	k = 0;
	if (dstsize < j || dstsize == 0)
		return (i + dstsize);
	while (str[k] && j + k < dstsize -1)
	{
		dest [j + k] = str[k];
		k ++;
	}
	dest [j + k] = '\0';
	return (j + i);
}
