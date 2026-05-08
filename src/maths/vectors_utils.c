/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:07:10 by ksudyn            #+#    #+#             */
/*   Updated: 2026/02/03 17:06:40 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
 * vectors_point()
 * ---------------
 * Suma un vector a un punto y devuelve un nuevo punto.
 *
 * Qué significa:
 * - Mover un punto en la dirección de un vector.
 *
 * Ejemplo:
 *   origen = (0, 0, 0)
 *   vector = (1, 2, 3)
 *   → resultado = (1, 2, 3)
 *
 * Uso en miniRT:
 * - Calcular el punto de impacto de un rayo
 * - Moverse a lo largo de un rayo
 */
t_point	vectors_point(t_point origin, t_vec vector)
{
	t_point	result;

	result.x = origin.x + vector.x;
	result.y = origin.y + vector.y;
	result.z = origin.z + vector.z;
	return (result);
}

/*
 * vector_zero()
 * -------------
 * Devuelve un vector con todos los valores a 0.
 *
 * Uso:
 * - Valor por defecto
 * - Para indicar errores o casos inválidos
 */

t_vec	vector_zero(void)
{
	t_vec	vector;

	vector.x = 0;
	vector.y = 0;
	vector.z = 0;
	return (vector);
}

/*
 * is_zero_vector()
 * ----------------
 * Comprueba si un vector es (0, 0, 0).
 *
 * Por qué es importante:
 * - Un vector cero no tiene dirección.
 * - No se puede normalizar.
 * - Se usa para detectar errores en el parseo o cálculos.
 */
bool	is_zero_vector(t_vec v)
{
	return (v.x == 0.0 && v.y == 0.0 && v.z == 0.0);
}

/*
 * module()
 * --------
 * Calcula la longitud de un vector.
 *
 * Ejemplo:
 *   (3, 4, 0) → 5
 *
 * Uso en miniRT:
 * - Normalizar vectores
 * - Calcular distancias
 */
double	module(t_vec vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y + vector.z
			* vector.z));
}

/*
 * normalize()
 * -----------
 * Convierte un vector en uno de longitud 1.
 *
 * Qué significa:
 * - Mantiene la dirección
 * - Elimina la magnitud
 *
 * Por qué es necesario:
 * - Rayos, normales y direcciones deben tener longitud 1
 * - Facilita cálculos de iluminación y proyecciones
 */
t_vec	normalize(t_vec vector)
{
	double	magnitude;

	magnitude = module(vector);
	vector.x /= magnitude;
	vector.y /= magnitude;
	vector.z /= magnitude;
	return (vector);
}

// “Uso estas funciones para trabajar con direcciones y posiciones en 3D,
// que son la base para calcular rayos, intersecciones y luz.”