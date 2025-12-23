/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 20:11:16 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/23 20:16:11 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Cuenta cuántas palabras hay en una línea separadas por espacios
static int	count_words(char *line)
{
	int		count;
	bool	inside_word;

	count = 0;
	while (line && *line)
	{
		inside_word = false;
		while (ft_isspace(*line) && *line)
			line++;
		while (!ft_isspace(*line) && *line)
		{
			if (!inside_word)
			{
				count++;
				inside_word = true;
			}
			line++;
		}
	}
	return (count);
}

// Obtiene la siguiente palabra de una línea
static char	*get_next_word(char *line, int *cursor)
{
	char	*word;
	int		length;
	int		i;

	length = 0;
	i = 0;
	while (ft_isspace(line[*cursor]))
		(*cursor)++;
	while (line[*cursor + length] && !ft_isspace(line[*cursor + length]))
		length++;
	word = malloc(sizeof(char) * (length + 1));
	if (!word)
		return (NULL);
	while (line[*cursor] && !ft_isspace(line[*cursor]))
		word[i++] = line[(*cursor)++];
	word[i] = '\0';
	return (word);
}

// Divide la línea en tokens separados por espacios
char	**split_line_by_space(char *line)
{
	int		words_count;
	char	**tokens;
	int		i;
	int		cursor;

	i = 0;
	cursor = 0;
	if (!line)
		return (free(line), NULL);
	words_count = count_words(line);
	tokens = malloc(sizeof(char *) * (words_count + 1));
	if (!tokens)
		return (free(line), NULL);
	while (words_count-- > 0)
		tokens[i++] = get_next_word(line, &cursor);
	tokens[i] = NULL;
	free(line);
	return (tokens);
}
