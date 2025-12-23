/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 12:28:07 by dgomez-l          #+#    #+#             */
/*   Updated: 2025/10/27 14:03:55 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

static char	**get_splited_line(int fd)
{
	char	*line;
	char	**sline;

	line = get_next_line(fd);
	sline = isspace_split(line);
	return (sline);
}

bool	read_file(t_scene *s, int fd)
{
	bool		error;
	t_parse		par;
	char		**sline;

	error = false;
	sline = get_splited_line(fd);
	while (sline && !error)
	{
		if (sline[0] != NULL)
		{
			par = get_type(sline[0]);
			if (check_format(s, sline, par.type, &error))
			{
				error = get_vals(sline, &par);
				if (!error)
					create_object(s, par);
			}
		}
		free_arr(sline);
		sline = get_splited_line(fd);
	}
	return (free_arr(sline), !error);
}
