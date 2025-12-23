/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:27:31 by alvaro            #+#    #+#             */
/*   Updated: 2025/09/10 13:22:29 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

t_obj	create_cylinder(t_point p, t_vec v, float rlen[2], t_color color)
{
	t_obj	c;

	c.type = CY;
	c.position.x = p.x;
	c.position.y = p.y;
	c.position.z = p.z;
	c.normal.x = v.x;
	c.normal.y = v.y;
	c.normal.z = v.z;
	c.normal = normalize(c.normal);
	c.diameter = 2 * rlen[0];
	c.height = rlen[1];
	c.color = color;
	return (c);
}

static double	limit_body(double distance0, double distance1, t_ray ray,
		t_obj obj)
{
	t_point		hit_position;
	double		height;

	if (distance0 > EPSILON)
	{
		hit_position = vectors_point(ray.origin, scale_vector(ray.direction,
					distance0));
		height = scalar_p(sub_points(hit_position, obj.position), obj.normal);
		if (fabs(height) <= (obj.height * 0.5) + EPSILON)
			return (distance0);
	}
	else
		distance0 = NOINTERSECTION;
	if (distance1 > EPSILON)
	{
		hit_position = vectors_point(ray.origin, scale_vector(ray.direction,
					distance1));
		height = scalar_p(sub_points(hit_position, obj.position), obj.normal);
		if (fabs(height) <= (obj.height * 0.5) + EPSILON)
			return (distance1);
	}
	else
		distance1 = NOINTERSECTION;
	return (NOINTERSECTION);
}

static double	calculate_coefficients(double *b, double *c, t_ray ray,
		t_obj obj)
{
	t_vec		ray_to_obj_center;
	t_vec		prj_ray_direction;
	t_vec		prj_ray_to_obj_direction;
	double		a;

	ray_to_obj_center = sub_points(ray.origin, obj.position);
	prj_ray_direction = sub_vectors(ray.direction, scale_vector(obj.normal,
				scalar_p(ray.direction, obj.normal)));
	prj_ray_to_obj_direction = sub_vectors(ray_to_obj_center,
			scale_vector(obj.normal, scalar_p(ray_to_obj_center, obj.normal)));
	a = scalar_p(prj_ray_direction, prj_ray_direction);
	*b = 2.0 * scalar_p(prj_ray_direction, prj_ray_to_obj_direction);
	*c = scalar_p(prj_ray_to_obj_direction, prj_ray_to_obj_direction)
		- (obj.diameter * 0.5) * (obj.diameter * 0.5);
	return (a);
}

double	compute_cylinder_intersection(t_ray ray, t_obj obj)
{
	double		a;
	double		b;
	double		c;
	double		disc;
	double		sqrt_disc;

	a = calculate_coefficients(&b, &c, ray, obj);
	if (fabs(a) < EPSILON)
		return (NOINTERSECTION);
	disc = b * b - 4.0 * a * c;
	if (disc < 0.0)
		return (NOINTERSECTION);
	sqrt_disc = sqrt(disc);
	return (limit_body((-b - sqrt_disc) / (2.0 * a), (-b + sqrt_disc) / (2.0
				* a), ray, obj));
}
