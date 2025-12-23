/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:24:23 by alvaro            #+#    #+#             */
/*   Updated: 2025/09/10 13:24:09 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

static void	register_closest_obj(double distance, double *min_distance,
		t_obj	*obj, t_obj **dst)
{
	if (distance < *min_distance && distance >= 0)
	{
		*min_distance = distance;
		*dst = obj;
	}
}

static t_intr	init_intr(double distance, t_ray ray, t_obj *obj)
{
	t_intr	intr;

	intr.position = (t_point){0};
	intr.normal = (t_vec){0};
	intr.obj = obj;
	if (intr.obj == NULL)
		return (intr);
	intr.position = vectors_point(ray.origin, scale_vector(ray.direction,
				distance));
	return (intr);
}

t_intr	get_intr(t_scene *scene, t_ray ray)
{
	int		i;
	double	min_distance;
	double	distance;
	t_intr	intr;
	t_obj	*obj;

	i = -1;
	min_distance = __DBL_MAX__;
	obj = NULL;
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
		register_closest_obj(distance, &min_distance, &scene->obj[i], &obj);
	}
	intr = init_intr(min_distance, ray, obj);
	return (intr);
}
