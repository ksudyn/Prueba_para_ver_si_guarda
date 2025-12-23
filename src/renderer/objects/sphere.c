/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:27:31 by alvaro            #+#    #+#             */
/*   Updated: 2025/09/24 00:35:43 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

t_obj	create_sphere(t_point p, float r, t_color c)
{
	t_obj	s;

	s.type = SP;
	s.position.x = p.x;
	s.position.y = p.y;
	s.position.z = p.z;
	s.diameter = 2 * r;
	s.color = c;
	return (s);
}

static double	calculate_disc(double *b, t_ray ray, t_obj obj)
{
	t_vec		ray_to_obj_center;
	double		disc;
	double		c;

	ray_to_obj_center = sub_points(ray.origin, obj.position);
	*b = 2.0 * scalar_p(ray.direction, ray_to_obj_center);
	c = scalar_p(ray_to_obj_center, ray_to_obj_center) - (obj.diameter * 0.5)
		* (obj.diameter * 0.5);
	disc = *b * *b - 4.0 * c;
	return (disc);
}

double	compute_sphere_intersection(t_ray ray, t_obj obj)
{
	double		disc;
	double		sqrt_disc;
	double		distance0;
	double		distance1;
	double		b;

	disc = calculate_disc(&b, ray, obj);
	if (disc < 0.0)
		return (NOINTERSECTION);
	sqrt_disc = sqrt(disc);
	distance0 = (-b - sqrt_disc) * 0.5;
	distance1 = (-b + sqrt_disc) * 0.5;
	if (distance0 > EPSILON)
		return (distance0);
	if (distance1 > EPSILON)
		return (distance1);
	return (NOINTERSECTION);
}
