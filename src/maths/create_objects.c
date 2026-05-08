/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:31:42 by ksudyn            #+#    #+#             */
/*   Updated: 2026/01/02 18:12:03 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * create_light(double brightness, t_point position, bool enabled)
 * --------------------------------------------------------------
 * Crea y devuelve una estructura t_light.
 *
 * Parámetros:
 * - brightness: intensidad de la luz (0.0 a 1.0)
 * - position: posición de la luz en el espacio
 * - enabled: estado activo/inactivo de la luz
 *
 * Cómo funciona:
 * - Inicializa los campos de la luz con los valores dados
 * - Devuelve la estructura lista para asignar a scene->light
 *
 * Relación con .rt:
 * - Cada línea tipo L del archivo genera un t_light.
 */

t_light	create_light(double brightness, t_point position, bool enabled)
{
	t_light	light;

	light.position = position;
	light.brightness = brightness;
	light.status = enabled;
	return (light);
}

/*
 * create_ambient(t_color color, double brightness, bool enabled)
 * -------------------------------------------------------------
 * Crea y devuelve una estructura t_ambient (luz ambiental).
 *
 * Parámetros:
 * - color: color de la luz ambiental
 * - brightness: intensidad de la luz (0.0 a 1.0)
 * - enabled: estado activo/inactivo
 *
 * Cómo funciona:
 * - Inicializa los campos y devuelve la estructura
 *
 * Relación con .rt:
 * - Cada línea tipo A del archivo genera un t_ambient.
 */

t_ambient	create_ambient(t_color color, double brightness, bool enabled)
{
	t_ambient	ambient;

	ambient.color = color;
	ambient.brightness = brightness;
	ambient.status = enabled;
	return (ambient);
}

/*
 * create_plane(t_point position, t_vec normal, t_color color)
 * ----------------------------------------------------------
 * Crea y devuelve un objeto plano (t_obj).
 *
 * Parámetros:
 * - position: punto base en el plano
 * - normal: vector normal al plano (se normaliza si no es cero)
 * - color: color del plano
 *
 * Cómo funciona:
 * - Si el vector normal es cero, asigna vector cero
 * - Normaliza el vector normal
 * - Asigna posición, color y tipo PLANE
 *
 * Relación con .rt:
 * - Cada línea "pl" del archivo genera un t_obj con tipo PLANE
 */

t_obj	create_plane(t_point position, t_vec normal, t_color color)
{
	t_obj	plane;

	plane.type = PLANE;
	plane.position = position;
	if (is_zero_vector(normal))
		plane.normal = vector_zero();
	else
		plane.normal = normalize(normal);
	plane.color = color;
	return (plane);
}

/*
 * create_sphere(t_point position, float radius, t_color color)
 * -----------------------------------------------------------
 * Crea y devuelve un objeto esfera (t_obj).
 *
 * Parámetros:
 * - position: centro de la esfera
 * - radius: radio de la esfera
 * - color: color de la esfera
 *
 * Cómo funciona:
 * - Calcula diámetro = 2 * radio
 * - Asigna posición, color y tipo SPHERE
 *
 * Relación con .rt:
 * - Cada línea "sp" del archivo genera un t_obj tipo SPHERE
 */

t_obj	create_sphere(t_point position, float radius, t_color color)
{
	t_obj	sphere;

	sphere.type = SPHERE;
	sphere.position = position;
	sphere.diameter = radius * 2.0f;
	sphere.color = color;
	return (sphere);
}

/*
 * create_cylinder(t_point position, t_vec axis, float values[2], t_color color)
 * -----------------------------------------------------------------------------
 * Crea y devuelve un objeto cilindro (t_obj).
 *
 * Parámetros:
 * - position: centro/base del cilindro
 * - axis: vector del eje del cilindro (normalizado)
 * - values[0]: radio
 * - values[1]: altura
 * - color: color del cilindro
 *
 * Cómo funciona:
 * - Normaliza el vector eje si no es cero
 * - Asigna diámetro = 2*radio y altura
 * - Asigna posición, color y tipo CYLINDER
 *
 * Relación con .rt:
 * - Cada línea "cy" del archivo genera un t_obj tipo CYLINDER
 */

t_obj	create_cylinder(t_point position, t_vec axis,
						float values[2], t_color color)
{
	t_obj	cylinder;

	cylinder.type = CYLINDER;
	cylinder.position = position;
	if (is_zero_vector(axis))
		cylinder.normal = vector_zero();
	else
		cylinder.normal = normalize(axis);
	cylinder.diameter = values[0] * 2.0f;
	cylinder.height = values[1];
	cylinder.color = color;
	return (cylinder);
}
