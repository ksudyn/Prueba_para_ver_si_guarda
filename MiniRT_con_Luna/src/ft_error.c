/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:45:47 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/23 20:11:07 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_error(char *file, int lineno, char **msg)
{
	char	*line_str;

	write(STDERR_FILENO, "Error\n", 6);
	if (lineno > 0 && file != NULL)
	{
		line_str = ft_itoa(lineno);
		if (!line_str)
			write(STDERR_FILENO, "malloc: fatal error\n", 20);
		else
		{
			write(STDERR_FILENO, file, ft_strlen(file));
			write(STDERR_FILENO, " - ", 3);
			write(STDERR_FILENO, line_str, ft_strlen(line_str));
			write(STDERR_FILENO, ": ", 2);
			free(line_str);
		}
	}
	while (msg && *msg)
	{
		write(STDERR_FILENO, *msg, ft_strlen(*msg));
		msg++;
	}
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	ft_error_close(int fd)
{
	if (close(fd) == ERROR)
	{
		ft_error(F, Z, (char *[]){"close: fatal error"});
		exit(EXIT_FAILURE);
	}
}