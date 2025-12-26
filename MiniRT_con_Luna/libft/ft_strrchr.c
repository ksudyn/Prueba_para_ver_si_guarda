/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:40:01 by ksudyn            #+#    #+#             */
/*   Updated: 2024/10/11 14:54:31 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	character;

	i = ft_strlen (s) -1;
	character = (unsigned char)c;
	if (character == '\0')
		return ((char *)&s[ft_strlen (s)]);
	while (i >= 0)
	{
		if (s[i] == character)
			return ((char *)(i + s));
		i--;
	}
	return (NULL);
}
