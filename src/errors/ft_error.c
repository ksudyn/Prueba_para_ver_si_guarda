/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:01:58 by asaiz-lo          #+#    #+#             */
/*   Updated: 2025/10/27 13:52:24 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

void	puterr(char *str)
{
	static bool	called = false;

	if (!called)
	{
		called = true;
		puterr("Error\n");
	}
	if (write(STDERR_FILENO, str, ft_strlen(str)) == ERROR)
		exit(EXIT_FAILURE);
}

void	err(char *file, int lineno, char **msg)
{
	char	*str;

	if (lineno > 0)
	{
		str = ft_itoa(lineno);
		if (str == NULL)
		{
			err(F, Z, (char *[]){"malloc: fatal error"});
			exit(EXIT_FAILURE);
		}
		puterr(file);
		puterr(" - ");
		puterr(str);
		puterr(": ");
		free(str);
	}
	while (*msg != NULL)
	{
		puterr(*msg);
		msg++;
	}
	puterr("\n");
	return ;
}

void	er_close(int fd)
{
	if (close(fd) == ERROR)
	{
		err(F, Z, (char *[]){"close: fatal error"});
		exit(EXIT_FAILURE);
	}
}
