/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:32:26 by ksudyn            #+#    #+#             */
/*   Updated: 2026/05/07 19:04:54 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * get_ray()
 * ---------
 * Transforma un píxel de la pantalla (x, y) en un rayo en el espacio 3D.
 * * Cómo funciona:
 * - Usa el FOV y el ratio de aspecto para situar el píxel en el mundo.
 * - El rayo sale de la cámara y atraviesa ese punto del "lienzo" imaginario.
 */
t_ray	get_ray(t_camera cam, int x, int y)
{
	t_ray	ray;
	double	px;
	double	py;
	t_vec	right;
	t_vec	up;

	px = (2.0 * (x + 0.5) / WIDTH - 1.0) * cam.scale * cam.ratio;
	py = (1.0 - 2.0 * (y + 0.5) / HEIGHT) * cam.scale;
	ray.origin = cam.position;
	right = scale_vector(cam.right, px);
	up = scale_vector(cam.up, py);
	ray.direction = normalize(add_vectors(cam.forward,
				add_vectors(right, up)));
	return (ray);
}

/*
 * init_shadow_ray()
 * -----------------
 * Prepara el rayo que usaremos para calcular las sombras.
 * * Cómo funciona:
 * - Sitúa el origen del rayo exactamente en el punto donde choca con el objeto.
 * - Calcula la dirección hacia la bombilla
 * 		restando la posición de la luz menos el impacto.
 * - Normaliza esa dirección para tener un vector de longitud 1.
 */
void	init_shadow_ray(t_light light, t_ray *ray, t_intr intr)
{
	t_vec	dir;

	ray->origin = intr.position;
	dir = sub_points(light.position, intr.position);
	if (is_zero_vector(dir))
		ray->direction = vector_zero();
	else
		ray->direction = normalize(dir);
}
