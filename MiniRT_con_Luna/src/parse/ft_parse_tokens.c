/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 20:11:16 by ksudyn            #+#    #+#             */
/*   Updated: 2026/02/03 17:08:01 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
 * count_words(const char *line)
 * ---------------------------------
 * Cuenta el número de palabras en una línea, separadas por espacios.
 *
 * Parámetros:
 * - line: cadena de caracteres (una línea del archivo .rt)
 *
 * Cómo funciona:
 * 1. Inicializa contador de palabras a 0 y marca que no estamos dentro de una palabra.
 * 2. Recorre cada carácter:
 *    - Si es espacio, inside_word = false.
 *    - Si no es espacio y no estábamos dentro de una palabra, incrementa count y marca inside_word = true.
 * 3. Devuelve el número de palabras encontradas.
 *
 * Relación con .rt:
 * - Divide líneas como:
 *   "sp 1,1,-4 2 255,0,0" → 4 palabras: ["sp", "1,1,-4", "2", "255,0,0"]
 *
 */

static int	count_words(const char *line)
{
	int		count;
	bool	inside_word;

	count = 0;
	inside_word = false;
	if (!line)
		return (0);
	while (*line)
	{
		if (ft_isspace(*line))
			inside_word = false;
		else if (!inside_word)
		{
			count++;
			inside_word = true;
		}
		line++;
	}
	return (count);
}

/*
 * get_next_word(const char *line, int *cursor)
 * ---------------------------------------------
 * Devuelve la siguiente palabra de la línea, empezando desde la posición *cursor.
 *
 * Parámetros:
 * - line: línea de texto
 * - cursor: índice actual dentro de la línea (se actualiza tras extraer la palabra)
 *
 * Cómo funciona:
 * 1. Avanza cursor hasta el primer carácter no espacio.
 * 2. Marca el inicio de la palabra (start).
 * 3. Avanza hasta el siguiente espacio o fin de línea (end).
 * 4. Si start < end, reserva memoria e copia la palabra.
 * 5. Retorna la palabra como string terminado en '\0'.
 *
 * Relación con .rt:
 * - Se usa para extraer cada token individual:
 *   "C 0,0,4 0,0,-1 70" → "C", "0,0,4", "0,0,-1", "70"
 *
 */

static char	*get_next_word(const char *line, int *cursor)
{
	char	*word;
	int		start;
	int		end;
	int		i;

	if (!line || !cursor)
		return (NULL);
	while (line[*cursor] && ft_isspace(line[*cursor]))
		(*cursor)++;
	start = *cursor;
	while (line[*cursor] && !ft_isspace(line[*cursor]))
		(*cursor)++;
	end = *cursor;
	if (end <= start)
		return (NULL);
	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = line[start++];
	word[i] = '\0';
	return (word);
}

/*
 * free_tokens(char **tokens, int count)
 * --------------------------------------
 * Libera un array de punteros a strings previamente alocado.
 *
 * Parámetros:
 * - tokens: array de char* (palabras)
 * - count: número de palabras que hay en el array
 *
 * Cómo funciona:
 * 1. Recorre cada token y libera su memoria.
 * 2. Finalmente, libera el array de punteros.
 *
 * Relación con .rt:
 * - Limpia la memoria después de procesar cada línea del archivo.
 *
 */

static void	free_tokens(char **tokens, int count)
{
	while (--count >= 0)
		free(tokens[count]);
	free(tokens);
}

/*
 * split_line_by_space(char *line)
 * --------------------------------
 * Divide una línea en tokens separados por espacios y devuelve un array de strings.
 *
 * Parámetros:
 * - line: línea de texto (se libera al final)
 *
 * Cómo funciona:
 * 1. Cuenta cuántas palabras tiene la línea con count_words().
 * 2. Reserva memoria para un array de punteros a char, tamaño words_count + 1.
 * 3. Recorre la línea y extrae cada palabra usando get_next_word().
 * 4. Si falla get_next_word(), libera todo con free_tokens() y retorna NULL.
 * 5. Coloca NULL al final del array y libera la línea original.
 *
 * Relación con .rt:
 * - Convierte:
 *   "cy -1,1,-4 0,-1,0 2 2 255,255,0"
 *   en un array de tokens: ["cy", "-1,1,-4", "0,-1,0", "2", "2", "255,255,0"]
 *
 */

char	**split_line_by_space(char *line)
{
	int		words_count;
	char	**tokens;
	int		i;
	int		cursor;

	if (!line)
		return (NULL);
	words_count = count_words(line);
	tokens = malloc(sizeof(char *) * (words_count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	cursor = 0;
	while (i < words_count)
	{
		tokens[i] = get_next_word(line, &cursor);
		if (!tokens[i])
			return (free_tokens(tokens, i), NULL);
		i++;
	}
	tokens[i] = NULL;
	free(line);
	return (tokens);
}

/*
 * read_next_line_tokens(int fd)
 * ------------------------------
 * Lee la siguiente línea del archivo y devuelve un array de tokens separados por espacios.
 *
 * Parámetros:
 * - fd: descriptor de archivo abierto
 *
 * Cómo funciona:
 * 1. Llama a get_next_line(fd) para leer la línea.
 * 2. Si no hay línea, retorna NULL (fin de archivo).
 * 3. Llama a split_line_by_space() para dividirla en tokens.
 * 4. Devuelve el array de tokens listo para parsear.
 *
 * Relación con .rt:
 * - Permite leer línea por línea de la escena:
 *   A 0.2 255,255,255
 *   C 0,0,4 0,0,-1 70
 *   ...
 * - Cada línea se convierte en array de strings para ser procesado por read_file().
 *
 */

char	**read_next_line_tokens(int fd)
{
	char	*line;
	char	**tokens;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	//printf("DEBUG: got line: \"%s\"\n", line);
	tokens = split_line_by_space(line);
	//printf("DEBUG: tokens ptr=%p\n", (void *)tokens);
	return (tokens);
}
