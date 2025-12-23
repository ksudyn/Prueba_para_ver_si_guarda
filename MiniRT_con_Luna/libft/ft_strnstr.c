/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:51:14 by alvaro            #+#    #+#             */
/*   Updated: 2024/03/20 18:52:33 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;
	char	*result;

	i = 0;
	if (*to_find == '\0')
		return ((char *)(str));
	while (str[i] != '\0' && i < n)
	{
		j = 0;
		if (str[i] == to_find[j])
		{
			result = (char *)&str[i];
			while (to_find[j] != '\0' && str[i + j] == to_find[j])
				j++;
			if (to_find[j] == '\0' && i + ft_strlen(to_find) <= n)
				return (result);
		}
		i++;
	}
	return (NULL);
}
