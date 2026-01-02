/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:48:49 by ksudyn            #+#    #+#             */
/*   Updated: 2026/01/02 18:17:39 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
 * get_camera_right(t_vec forward)
 * -------------------------------
 * Calcula el vector "right" de la cámara para el sistema de coordenadas local.
 *
 * Cómo funciona:
 * - Usa up = (0,1,0) por defecto.
 * - Si forward está casi paralelo a up, cambia up = (0,0,1) para evitar colinealidad.
 * - Devuelve producto vectorial: right = forward × up.
 *
 * Relación con el raytracer:
 * - right y up se usan para generar rayos de cada píxel correctamente orientados.
 */

static t_vec	get_camera_right(t_vec forward)
{
	t_vec	up;

	up.x = 0;
	up.y = 1;
	up.z = 0;
	if (fabs(scalar_p(forward, up)) > 0.99)
	{
		up.x = 0;
		up.y = 0;
		up.z = 1;
	}
	return (vectorial_p(forward, up));
}

/*
 * create_camera(t_point position, t_vec forward, double fov, bool raw)
 * -------------------------------------------------------------------
 * Crea un objeto cámara (CAMERA) listo para raytracing.
 *
 * Cómo funciona:
 * - Asigna posición y dirección normalizada.
 * - Asigna escala (fov o tangente del fov si raw=true).
 * - Calcula vectores right y up para el sistema de la cámara.
 * - Calcula ratio de aspecto (WIDTH / HEIGHT).
 *
 * Relación con .rt:
 * - Línea: C x,y,z dir_x,dir_y,dir_z fov
 *   → se convierte en scene->camera
 */

t_camera	create_camera(t_point position, t_vec forward, double fov, bool raw)
{
	t_camera	camera;

	camera.status = true;
	camera.position = position;
	if (is_zero_vector(forward))
		camera.forward = vector_zero();
	else
		camera.forward = normalize(forward);
	camera.scale = fov;
	if (raw)
		camera.scale = tan(fov * PI / 360.0);
	camera.right = get_camera_right(camera.forward);
	camera.up = vectorial_p(camera.right, camera.forward);
	camera.ratio = (double)WIDTH / (double)HEIGHT;
	return (camera);
}
