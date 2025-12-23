/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 20:07:16 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/23 20:16:18 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Función principal de parseo
bool	ft_parse(char *filename, t_scene *scene)
{
	int		fd;
	bool	status;

	if (!is_rt(filename))
	{
		ft_error(F, Z, (char *[]){"File must be *.rt\n", NULL});
		return (false);
	}
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
	{
		ft_error(F, Z, (char *[]){"Could not open the file\n", NULL});
		return (false);
	}
	status = read_file(scene, fd);
	if (!scene->camera.status)
	{
		ft_error(F, Z, (char *[]){"Camera missing in config.\n", NULL});
		status = false;
	}
	close(fd);
	return (status);
}
