/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:49:23 by ksudyn            #+#    #+#             */
/*   Updated: 2026/02/03 17:06:12 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
 * sub_points()
 * ------------
 * Resta dos puntos 3D y devuelve un vector.
 *
 * Qué significa:
 * - Devuelve el vector que va desde el punto B hasta el punto A.
 *
 * Ejemplo:
 *   A = (3, 2, 1)
 *   B = (1, 1, 1)
 *   → resultado = (2, 1, 0)
 *
 * Uso en miniRT:
 * - Calcular direcciones
 * - Calcular normales
 * - Calcular rayos desde la cámara a los objetos
 */
t_vec	sub_points(t_point a, t_point b)
{
	t_vec	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

/*
 * scalar_p()
 * ----------
 * Calcula el producto escalar entre dos vectores.
 *
 * Qué indica:
 * - Si el resultado es positivo → apuntan en la misma dirección
 * - Si es negativo → apuntan en direcciones opuestas
 * - Si es 0 → son perpendiculares
 *
 * Uso en miniRT:
 * - Saber si una normal apunta hacia el rayo
 * - Calcular iluminación (ángulo entre luz y superficie)
 */
double	scalar_p(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
