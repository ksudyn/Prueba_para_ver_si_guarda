/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:51:47 by ksudyn            #+#    #+#             */
/*   Updated: 2026/01/02 17:53:17 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	calculate_discriminant(double *b, t_ray ray, t_obj obj)
{
	t_vec	oc;
	double	c;

	oc = sub_points(ray.origin, obj.position);
	*b = 2.0 * scalar_p(ray.direction, oc);
	c = scalar_p(oc, oc) - pow(obj.diameter * 0.5, 2);
	return ((*b * *b) - (4.0 * c));
}

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
