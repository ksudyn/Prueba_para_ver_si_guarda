/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:27:59 by alvaro            #+#    #+#             */
/*   Updated: 2025/09/29 11:39:57 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

t_ray	get_ray(t_camera camera, int x, int y)
{
	double		px;
	double		py;
	t_vec		right;
	t_vec		up;
	t_ray		ray;

	px = (2.0 * (x + 0.5) / (double)WIDTH - 1.0) * camera.scale * camera.ratio;
	py = (1.0 - 2.0 * (y + 0.5) / (double)HEIGHT) * camera.scale;
	ray.origin = camera.position;
	right = scale_vector(camera.right, px);
	up = scale_vector(camera.up, py);
	ray.direction = normalize(add_vectors(camera.forward, add_vectors(right,
					up)));
	return (ray);
}

// if the new_ray cam.o-light, intersects the object before the light,
// the light is inside

bool	avoid_inside_lights(t_ray ray, t_intr intrs)
{
	double		distance;

	if (intrs.obj->type == SP)
		distance = compute_sphere_intersection(ray, *(intrs.obj));
	else if (intrs.obj->type == CY)
		distance = compute_cylinder_intersection(ray, *(intrs.obj));
	else
		return (false);
	return (distance != NOINTERSECTION);
}

// cpy of get intersections but shooying the ray from the object to see if 
// any light is reaching it
bool	is_shadowed(t_scene *scene, t_ray ray, t_intr intrs)
{
	int			i;
	double		distance;
	double		distance_to_light;

	distance_to_light = module(sub_points(scene->light.position,
				ray.origin));
	i = -1;
	while (++i < scene->obj_num)
	{
		if (scene->obj[i].type == PL)
			distance = compute_plane_intersection(ray, scene->obj[i]);
		else if (scene->obj[i].type == SP)
			distance = compute_sphere_intersection(ray, scene->obj[i]);
		else if (scene->obj[i].type == CY)
			distance = compute_cylinder_intersection(ray, scene->obj[i]);
		else
			distance = NOINTERSECTION;
		if (distance != NOINTERSECTION && distance < distance_to_light)
			return (true);
	}
	return (avoid_inside_lights(ray, intrs));
}
