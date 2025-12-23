/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:28:06 by alvaro            #+#    #+#             */
/*   Updated: 2025/09/10 11:40:02 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	int		i;
	char	*aux;

	aux = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			aux = (char *)&s[i];
		i++;
	}
	if ((unsigned char)c == 0)
		return ((char *)&s[i]);
	return (aux);
}

/*
int	main(int ac, char *av[])
{
	printf("%s\n", ft_strrchr(av[1], *av[2]));
	return 0;
}*/
