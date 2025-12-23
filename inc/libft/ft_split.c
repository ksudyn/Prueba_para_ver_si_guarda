/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 13:33:39 by asaiz-lo          #+#    #+#             */
/*   Updated: 2024/08/13 18:20:22 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_countword(char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		count += (*s != 0);
		while (*s != c && *s)
			s++;
	}
	return (count);
}

void	freelst(char **lst, int lim)
{
	int	i;

	i = 0;
	while (i < lim)
		free(lst[i++]);
	free(lst);
}

char	**ft_split(char *s, char c)
{
	char	**lst;
	size_t	word_len;
	int		i;

	lst = (char **)malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!s || !lst)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				word_len = ft_strlen(s);
			else
				word_len = ft_strchr(s, c) - s;
			lst[i++] = ft_substr(s, 0, word_len);
			if (lst[i - 1] == NULL)
				return (freelst(lst, i - 1), NULL);
			s += word_len;
		}
	}
	return (lst[i] = NULL, lst);
}

// int main(int ac, char *av[])
//{
//	if(!ac)
//		return (-1);
//	char **strs = ft_split("1 2 3 4", ' ');
//
//	for(int i = 0; strs[i]; i++)
//		printf("\n%s", strs[i]);
//	return (0);
//}
