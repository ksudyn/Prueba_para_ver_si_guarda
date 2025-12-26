/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:55:03 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/26 18:40:06 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

static double	solve_quadratic(double a, double b, double c,
		t_ray ray, t_obj obj)
{
	double	disc;
	double	sqrt_disc;
	double	t0;
	double	t1;

	disc = (b * b) - (4.0 * a * c);
	if (disc < 0.0)
		return (NOINTERSECTION);
	sqrt_disc = sqrt(disc);
	t0 = (-b - sqrt_disc) / (2.0 * a);
	t1 = (-b + sqrt_disc) / (2.0 * a);
	t0 = check_height(t0, ray, obj);
	if (t0 != NOINTERSECTION)
		return (t0);
	return (check_height(t1, ray, obj));
}

double	compute_cylinder_intersection(t_ray ray, t_obj obj)
{
	t_vec	oc;
	t_vec	d;
	t_vec	x;
	double	a;
	double	b;
	double	c;

	oc = sub_points(ray.origin, obj.position);
	d = sub_vectors(ray.direction,
			scale_vector(obj.normal, scalar_p(ray.direction, obj.normal)));
	x = sub_vectors(oc,
			scale_vector(obj.normal, scalar_p(oc, obj.normal)));
	a = scalar_p(d, d);
	if (fabs(a) < EPSILON)
		return (NOINTERSECTION);
	b = 2.0 * scalar_p(d, x);
	c = scalar_p(x, x) - pow(obj.diameter * 0.5, 2);
	return (solve_quadratic(a, b, c, ray, obj));
}
