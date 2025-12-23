/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:11:01 by alvaro            #+#    #+#             */
/*   Updated: 2024/03/20 18:30:54 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	unsigned char	*dest;
	unsigned char	*srce;

	dest = dst;
	srce = (unsigned char *)src;
	if (srce > dest)
	{
		i = 0;
		while (i < len)
		{
			dest[i] = srce[i];
			i++;
		}
	}
	else if (srce < dest)
	{
		i = len;
		while (i > 0)
		{
			i--;
			dest[i] = srce[i];
		}
	}
	return (dest);
}
