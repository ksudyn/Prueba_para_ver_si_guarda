/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_space_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 22:17:19 by asaiz-lo          #+#    #+#             */
/*   Updated: 2025/09/10 13:06:10 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft/libft.h"

static int	count_words(char *str)
{
	int		count;
	bool	inside_word;

	count = 0;
	while (str && *str)
	{
		inside_word = false;
		while (ft_isspace(*str) && *str)
			++str;
		while (!ft_isspace(*str) && *str)
		{
			if (!inside_word)
			{
				++count;
				inside_word = true;
			}
			++str;
		}
	}
	return (count);
}

static char	*get_next_word(char *str, int *cursor)
{
	char		*next_str;
	int			len;
	int			i;

	len = 0;
	i = 0;
	while (ft_isspace(str[(*cursor)]))
		(*cursor)++;
	while ((!ft_isspace(str[(*cursor) + len])) && str[(*cursor) + len])
		len++;
	next_str = malloc((size_t)len * sizeof(char) + 1);
	if (NULL == next_str)
		return (NULL);
	while ((!ft_isspace(str[*cursor])) && str[*cursor])
		next_str[i++] = str[(*cursor)++];
	next_str[i] = '\0';
	return (next_str);
}

char	**isspace_split(char *str)
{
	int		words_number;
	char	**ret;
	int		i;
	int		cursor;

	if (!str)
		return (free(str), NULL);
	i = 0;
	cursor = 0;
	words_number = count_words(str);
	ret = malloc(sizeof(char *) * (size_t)(words_number + 1));
	if (NULL == ret)
		return (free(str), NULL);
	if (!words_number)
		return (free(str), ret[0] = NULL, ret);
	while (words_number-- >= 1)
		ret[i++] = get_next_word(str, &cursor);
	ret[i] = NULL;
	free(str);
	return (ret);
}
