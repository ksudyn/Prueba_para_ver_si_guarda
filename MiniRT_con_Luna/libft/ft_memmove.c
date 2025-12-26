/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:04:28 by ksudyn            #+#    #+#             */
/*   Updated: 2024/10/10 14:54:48 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if ((d > s) && (s + len > d))
	{
		while (len--)
			d[len] = s[len];
	}
	else
		ft_memcpy(d, s, len);
	return (dest);
}
