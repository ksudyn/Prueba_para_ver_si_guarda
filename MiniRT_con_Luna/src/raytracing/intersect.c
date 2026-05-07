/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:32:57 by ksudyn            #+#    #+#             */
/*   Updated: 2026/05/07 19:02:40 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * register_closest()
 * ------------------
 * Actualiza cuál es el objeto más cercano encontrado hasta el momento.
 * * Cómo funciona:
 * - Compara la distancia del nuevo choque con la distancia mínima guardada.
 * - Si el objeto está más cerca que el anterior,
 * 		actualiza el valor de `min` y guarda el objeto.
 */
static void	register_closest(double dist, double *min, t_obj *obj, t_obj **hit)
{
	if (dist >= 0 && dist < *min)
	{
		*min = dist;
		*hit = obj;
	}
}

/*
 * get_intersection()
 * ------------------
 * Recorre todos los objetos de la escena para ver
 * 		cuál es el primero que toca el rayo.
 * * Cómo funciona:
 * - Lanza el rayo contra cada esfera, plano y cilindro de la lista.
 * - Guarda únicamente el objeto que esté a la distancia más corta
 * 		(el que vemos primero).
 * - Devuelve una estructura con el objeto golpeado
 * 		y el punto exacto del choque.
 */
t_intr	get_intersection(t_scene *scene, t_ray ray)
{
	t_intr	intr;
	double	min;
	double	d;
	int		i;
	t_obj	*obj;

	min = __DBL_MAX__;
	obj = NULL;
	i = -1;
	while (++i < scene->obj_num)
	{
		if (scene->obj[i].type == PLANE)
			d = compute_plane_intersection(ray, scene->obj[i]);
		else if (scene->obj[i].type == SPHERE)
			d = compute_sphere_intersection(ray, scene->obj[i]);
		else
			d = compute_cylinder_intersection(ray, scene->obj[i]);
		register_closest(d, &min, &scene->obj[i], &obj);
	}
	intr.obj = obj;
	if (!obj)
		return (intr);
	intr.position = vectors_point(ray.origin, scale_vector(ray.direction, min));
	return (intr);
}
