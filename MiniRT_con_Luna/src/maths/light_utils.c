/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:49:07 by ksudyn            #+#    #+#             */
/*   Updated: 2026/02/03 17:05:30 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
 * get_plane_normal()
 * ------------------
 * Devuelve la normal correcta de un plano en el punto de intersección.
 *
 * Qué hace:
 * - Usa la normal del plano definida en el archivo .rt.
 * - Comprueba si la normal apunta en la misma dirección que el rayo.
 * - Si apunta hacia dentro del plano, la gira.
 *
 * Por qué es necesario:
 * - Un plano tiene dos caras.
 * - La normal debe apuntar hacia el lado visible por la cámara.
 */
static t_vec	get_plane_normal(t_intr intr, t_ray ray)
{
	if (scalar_p(ray.direction, intr.obj->normal) > 0)
		return (intr.obj->normal);
	return (flip_vector(intr.obj->normal));
}

/*
 * get_sphere_normal()
 * -------------------
 * Calcula la normal de una esfera en el punto donde el rayo la toca.
 *
 * Qué hace:
 * 1. Calcula el vector desde el centro de la esfera hasta el punto de impacto.
 * 2. Normaliza ese vector para obtener la dirección.
 * 3. Comprueba si la normal apunta en la misma dirección que el rayo.
 * 4. Si apunta hacia dentro, la gira.
 *
 * Ejemplo:
 * - Si el rayo toca la esfera por fuera,
 *   la normal apunta hacia fuera.
 *
 * Por qué es necesario:
 * - La iluminación depende del ángulo entre la luz y la normal.
 */
static t_vec	get_sphere_normal(t_intr intr, t_ray ray)
{
	t_vec	normal;

	normal = sub_points(intr.position, intr.obj->position);
	if (is_zero_vector(normal))
		return (vector_zero());
	normal = normalize(normal);
	if (scalar_p(ray.direction, normal) > 0)
		return (normal);
	return (flip_vector(normal));
}

/*
 * get_cylinder_normal()
 * ---------------------
 * Calcula la normal del cilindro en el punto donde el rayo lo toca.
 *
 * Qué hace:
 * 1. Calcula el vector desde el centro del cilindro al punto de impacto.
 * 2. Elimina la parte del vector que va en la dirección del eje del cilindro.
 * 3. Lo que queda apunta hacia fuera del cilindro.
 * 4. Normaliza ese vector.
 * 5. Si apunta hacia dentro respecto al rayo, lo gira.
 *
 * Por qué es necesario:
 * - El cilindro no es una esfera: su normal no sale del centro,
 *   sino de la superficie lateral.
 */
static t_vec	get_cylinder_normal(t_intr intr, t_ray ray)
{
	t_vec	from_center;
	t_vec	projection;
	double	axial_dot;

	from_center = sub_points(intr.position, intr.obj->position);
	axial_dot = scalar_p(from_center, intr.obj->normal);
	projection = scale_vector(intr.obj->normal, axial_dot);
	from_center = sub_vectors(from_center, projection);
	if (is_zero_vector(from_center))
		return (vector_zero());
	from_center = normalize(from_center);
	if (scalar_p(ray.direction, from_center) > 0)
		return (from_center);
	return (flip_vector(from_center));
}

/*
 * get_normal()
 * ------------
 * Decide qué función usar para calcular la normal según el tipo de objeto.
 *
 * Qué hace:
 * - Si es un plano → usa get_plane_normal
 * - Si es una esfera → usa get_sphere_normal
 * - Si es un cilindro → usa get_cylinder_normal
 *
 * Uso:
 * - Se llama justo después de detectar una intersección.
 * - El resultado se usa para calcular la iluminación.
 */
t_vec	get_normal(t_intr intr, t_ray ray)
{
	if (intr.obj->type == PLANE)
		return (get_plane_normal(intr, ray));
	if (intr.obj->type == SPHERE)
		return (get_sphere_normal(intr, ray));
	if (intr.obj->type == CYLINDER)
		return (get_cylinder_normal(intr, ray));
	return (vector_zero());
}

// “Primero calculo dónde el rayo toca el objeto y después calculo la normal para saber qué cara del objeto
// está mirando a la cámara, lo que es necesario para aplicar la iluminación correctamente.”