/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:54:19 by ksudyn            #+#    #+#             */
/*   Updated: 2026/05/07 18:49:52 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * compute_plane_intersection()
 * ----------------------------
 * Calcula si un rayo choca con una superficie plana infinita.
 * * Cómo funciona:
 * - Compara la dirección del rayo con la del plano (producto escalar).
 * - Si son perpendiculares, el rayo es paralelo y nunca chocará.
 * - Si no, calcula a qué distancia "t" se cruzan.
 */
double	compute_plane_intersection(t_ray ray, t_obj obj)
{
	double	denom;
	double	t;
	t_vec	p0l0;

	denom = scalar_p(obj.normal, ray.direction);
	if (fabs(denom) < EPSILON)
		return (NOINTERSECTION);
	p0l0 = sub_points(obj.position, ray.origin);
	t = scalar_p(p0l0, obj.normal) / denom;
	if (t > EPSILON)
		return (t);
	return (NOINTERSECTION);
}
