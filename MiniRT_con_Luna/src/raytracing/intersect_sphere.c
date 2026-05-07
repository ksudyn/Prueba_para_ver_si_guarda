/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:51:47 by ksudyn            #+#    #+#             */
/*   Updated: 2026/05/07 19:01:19 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * calculate_discriminant()
 * ------------------------
 * Realiza el cálculo matemático central para la intersección con esferas.
 * * Cómo funciona:
 * - Calcula el término 'b' y el término 'c' de la ecuación cuadrática.
 * - Devuelve el determinante ($b^2 - 4ac$).
 * - Si el resultado es positivo, significa que el rayo atraviesa la esfera.
 */
static double	calculate_discriminant(double *b, t_ray ray, t_obj obj)
{
	t_vec	oc;
	double	c;

	oc = sub_points(ray.origin, obj.position);
	*b = 2.0 * scalar_p(ray.direction, oc);
	c = scalar_p(oc, oc) - pow(obj.diameter * 0.5, 2);
	return ((*b * *b) - (4.0 * c));
}

/*
 * compute_sphere_intersection()
 * -----------------------------
 * Detecta si el rayo atraviesa una esfera.
 * * Cómo funciona:
 * - Usa la fórmula matemática de intersección rayo-esfera.
 * - Si el discriminante es positivo, el rayo entra y sale de la esfera.
 * - Devuelve la distancia "t" más pequeña (el primer punto que toca).
 */
double	compute_sphere_intersection(t_ray ray, t_obj obj)
{
	double	disc;
	double	sqrt_disc;
	double	b;
	double	t0;
	double	t1;

	disc = calculate_discriminant(&b, ray, obj);
	if (disc < 0.0)
		return (NOINTERSECTION);
	sqrt_disc = sqrt(disc);
	t0 = (-b - sqrt_disc) * 0.5;
	t1 = (-b + sqrt_disc) * 0.5;
	if (t0 > EPSILON)
		return (t0);
	if (t1 > EPSILON)
		return (t1);
	return (NOINTERSECTION);
}
