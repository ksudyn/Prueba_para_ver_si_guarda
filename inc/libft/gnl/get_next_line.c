/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:02:24 by alvaro            #+#    #+#             */
/*   Updated: 2025/10/20 20:57:42 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*limpiar_guardado(char *guardado)
{
	char	*final;
	char	*nuevo;
	int		len;

	final = ft_strchr(guardado, '\n');
	if (!final)
	{
		nuevo = NULL;
		free(guardado);
		return (guardado = NULL, NULL);
	}
	else
		len = (final - guardado) + 1;
	if (!guardado[len])
	{
		free(guardado);
		return (guardado = NULL, NULL);
	}
	nuevo = ft_substr(guardado, len, ft_strlen(guardado) - len);
	free(guardado);
	guardado = NULL;
	return (nuevo);
}

char	*extraer_linea(char *guardado)
{
	char	*linea;
	char	*final;
	int		len;

	final = ft_strchr(guardado, '\n');
	len = (final - guardado + 1);
	linea = ft_substr(guardado, 0, len);
	if (!linea)
		return (NULL);
	return (linea);
}

char	*procesar_linea(int fd, char *guardado, char *is_eof)
{
	int		check;
	char	*buffer;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (free(guardado), NULL);
	check = 1;
	buffer[0] = '\0';
	while ((check > 0 && !ft_strchr(buffer, '\n')) && *is_eof != 42)
	{
		check = read(fd, buffer, BUFFER_SIZE);
		if (ft_strnchr(buffer, '\0', check) < ft_strnchr(buffer, '\n', check))
			*is_eof = 42;
		if (check > 0)
		{
			buffer[check] = '\0';
			guardado = ft_strjoin(guardado, buffer);
		}
	}
	if (check == -1)
	{
		free(guardado);
		return (guardado = NULL, NULL);
	}
	return (free(buffer), guardado);
}

char	*get_next_line(int fd)
{
	static char	*guardado = {0};
	char		*line;
	static char	is_eof;

	if (is_eof == 42)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (is_eof = 0, free(guardado), guardado = NULL, NULL);
	if ((guardado && !ft_strchr(guardado, '\n')) || !guardado)
		guardado = procesar_linea(fd, guardado, &is_eof);
	if (!guardado)
		return (NULL);
	line = extraer_linea(guardado);
	if (!line)
		return (is_eof = 0, free(guardado), guardado = NULL, NULL);
	guardado = limpiar_guardado(guardado);
	return (line);
}
