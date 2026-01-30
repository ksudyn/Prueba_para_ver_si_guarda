/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 20:07:16 by ksudyn            #+#    #+#             */
/*   Updated: 2026/01/30 16:51:29 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
 * ft_parse(char *filename, t_scene *scene)
 * ----------------------------------------
 * Función principal del parseo.
 * Es la entrada desde main().
 *
 * Qué hace:
 * 1. Comprueba que el archivo tenga extensión .rt.
 * 2. Abre el archivo en modo lectura.
 * 3. Llama a read_file para leer y procesar todo el contenido.
 * 4. Verifica que exista al menos una cámara en la escena.
 * 5. Cierra el archivo y devuelve el resultado.
 *
 * Si algo falla:
 * - Muestra un mensaje de error.
 * - Devuelve false.
 */
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
	{// Verifica que haya al menos una cámara en el archivo
		ft_error(F, Z, (char *[]){"Camera missing in config.\n", NULL});
		status = false;
	}
	close(fd);
	return (status);
}
