/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:27:31 by alvaro            #+#    #+#             */
/*   Updated: 2024/10/22 12:36:47 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

t_obj	create_plane(t_point point, t_vec v, t_color c)
{
	t_obj	p;

	p.type = PL;
	p.position.x = point.x;
	p.position.y = point.y;
	p.position.z = point.z;
	p.normal.x = v.x;
	p.normal.y = v.y;
	p.normal.z = v.z;
	p.color = c;
	return (p);
}

//dis=(P0-O)⋅n / d⋅n ===
// (ray_to_obj_center)·obj.normal / ray.direction·obj.normal

// n = normal plane
// d = ray's vector 
// P (punto cualquiera del plano)
// O ray's origin
double	compute_plane_intersection(t_ray ray, t_obj obj)
{
	double		denom;
	double		numerator;
	double		distance;
	t_vec		ray_to_obj_center;

	ray_to_obj_center = sub_points(obj.position, ray.origin);
	denom = scalar_p(obj.normal, ray.direction);
	if (fabs(denom) < EPSILON)
		return (NOINTERSECTION);
	numerator = scalar_p(ray_to_obj_center, obj.normal);
	distance = numerator / denom;
	if (distance > EPSILON)
	{
		return (distance);
	}
	return (NOINTERSECTION);
}
