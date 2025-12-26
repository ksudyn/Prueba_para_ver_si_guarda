/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:16:41 by ksudyn            #+#    #+#             */
/*   Updated: 2024/10/10 14:45:28 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] && (i < len))
	{
		j = 0;
		while (str[i + j] == to_find[j] && i + j < len)
		{
			if (to_find[j + 1] == '\0')
				return (i + (char *)str);
			j++;
		}
		i++;
	}
	return (NULL);
}
