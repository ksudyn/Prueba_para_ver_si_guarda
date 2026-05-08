/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:55:03 by ksudyn            #+#    #+#             */
/*   Updated: 2026/05/07 19:06:31 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * check_height()
 * --------------
 * Comprueba si el punto de choque está dentro de los límites del cilindro.
 * * Cómo funciona:
 * - Calcula el punto exacto en el espacio donde el rayo toca
 * 		el cilindro infinito.
 * - Mide la distancia desde el centro del cilindro
 * 		hasta ese punto a lo largo de su eje.
 * - Si esa distancia es mayor que la mitad de la altura,
 * 		el choque no es válido.
 */
static double	check_height(double t, t_ray ray, t_obj obj)
{
	t_point	p;
	double	h;

	if (t <= EPSILON)
		return (NOINTERSECTION);
	p = vectors_point(ray.origin, scale_vector(ray.direction, t));
	h = scalar_p(sub_points(p, obj.position), obj.normal);
	if (fabs(h) <= (obj.height * 0.5) + EPSILON)
		return (t);
	return (NOINTERSECTION);
}

/*
 * solve_quadratic()
 * -----------------
 * Resuelve la ecuación de segundo grado para encontrar el punto de choque.
 * * Cómo funciona:
 * - Calcula el discriminante. Si es negativo, el rayo no toca el objeto.
 * - Calcula las dos posibles distancias (t0 y t1).
 * - Usa check_height
 * 		para asegurar que el choque cae dentro del cuerpo del cilindro.
 */
static double	solve_quadratic(t_quad q)
{
	double	disc;
	double	sqrt_disc;
	double	t0;
	double	t1;

	disc = (q.b * q.b) - (4.0 * q.a * q.c);
	if (disc < 0.0)
		return (NOINTERSECTION);
	sqrt_disc = sqrt(disc);
	t0 = (-q.b - sqrt_disc) / (2.0 * q.a);
	t1 = (-q.b + sqrt_disc) / (2.0 * q.a);
	t0 = check_height(t0, q.ray, q.obj);
	if (t0 != NOINTERSECTION)
		return (t0);
	return (check_height(t1, q.ray, q.obj));
}

/*
 * compute_cylinder_intersection()
 * -------------------------------
 * Lógica principal para detectar si un rayo choca con un cilindro.
 * * Cómo funciona:
 * - Reduce el problema 3D a una ecuación cuadrática (a, b, c).
 * - Proyecta el rayo sobre el plano perpendicular al eje del cilindro.
 * - Si hay solución, devuelve la distancia más cercana.
 */
double	compute_cylinder_intersection(t_ray ray, t_obj obj)
{
	t_cyl	c;
	t_quad	q;

	c.oc = sub_points(ray.origin, obj.position);
	c.d = sub_vectors(ray.direction,
			scale_vector(obj.normal, scalar_p(ray.direction, obj.normal)));
	c.x = sub_vectors(c.oc,
			scale_vector(obj.normal, scalar_p(c.oc, obj.normal)));
	c.a = scalar_p(c.d, c.d);
	if (fabs(c.a) < EPSILON)
		return (NOINTERSECTION);
	c.b = 2.0 * scalar_p(c.d, c.x);
	c.c = scalar_p(c.x, c.x) - pow(obj.diameter * 0.5, 2);
	q.a = c.a;
	q.b = c.b;
	q.c = c.c;
	q.ray = ray;
	q.obj = obj;
	return (solve_quadratic(q));
}
