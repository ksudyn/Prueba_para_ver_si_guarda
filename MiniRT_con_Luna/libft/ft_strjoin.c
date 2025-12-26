/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:16:23 by ksudyn            #+#    #+#             */
/*   Updated: 2025/09/24 17:28:57 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*dst;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	dst = ft_calloc(lens1 + lens2 + 1, sizeof(char));
	if (!dst)
		return (NULL);
	ft_memcpy(dst, s1, lens1);
	ft_memcpy(dst + lens1, s2, lens2);
	dst[lens1 + lens2] = '\0';
	return (dst);
}
