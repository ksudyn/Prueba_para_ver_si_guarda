/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:06:58 by ksudyn            #+#    #+#             */
/*   Updated: 2026/02/03 17:03:08 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
 * vectorial_p()
 * -------------
 * Calcula un vector perpendicular a otros dos vectores.
 *
 * Qué hace:
 * - Devuelve un vector que es perpendicular a A y a B.
 * - El resultado se normaliza (longitud 1).
 *
 * Por qué es importante:
 * - Se usa para calcular la orientación de la cámara.
 * - Se usa para obtener vectores "right" y "up".
 *
 * Nota:
 * - Si el resultado es un vector cero, devuelve (0,0,0)
 *   para evitar errores.
 */
t_vec	vectorial_p(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	if (is_zero_vector(result))
		return (vector_zero());
	return (normalize(result));
}//“Dame un vector que apunte a un lado, a partir de dos direcciones”

/*
 * add_vectors()
 * -------------
 * Suma dos vectores componente a componente.
 *
 * Uso:
 * - Combinar direcciones
 * - Calcular nuevas direcciones de rayos
 */
t_vec	add_vectors(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

/*
 * sub_vectors()
 * -------------
 * Resta un vector a otro.
 *
 * Qué significa:
 * - Devuelve la dirección que va desde B hasta A.
 *
 * Uso:
 * - Cálculos de normales
 * - Ajustes de direcciones
 */
t_vec	sub_vectors(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

/*
 * scale_vector()
 * --------------
 * Multiplica un vector por un número.
 *
 * Qué significa:
 * - Cambia el tamaño del vector
 * - Mantiene la dirección
 *
 * Uso:
 * - Avanzar a lo largo de un rayo
 * - Ajustar distancias
 */
t_vec	scale_vector(t_vec vector, double scale)
{
	vector.x *= scale;
	vector.y *= scale;
	vector.z *= scale;
	return (vector);
}

/*
 * flip_vector()
 * -------------
 * Invierte la dirección de un vector.
 *
 * Ejemplo:
 *   (1, 0, 0) → (-1, 0, 0)
 *
 * Uso:
 * - Corregir normales
 * - Asegurar que la normal mira hacia la cámara
 */
t_vec	flip_vector(t_vec vector)
{
	vector.x *= -1;
	vector.y *= -1;
	vector.z *= -1;
	return (vector);
}
