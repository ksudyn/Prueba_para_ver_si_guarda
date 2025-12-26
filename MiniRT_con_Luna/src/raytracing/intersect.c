/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:32:57 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/26 18:39:52 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	register_closest(double dist, double *min, t_obj *obj, t_obj **hit)
{
	if (dist >= 0 && dist < *min)
	{
		*min = dist;
		*hit = obj;
	}
}

t_intr	get_intersection(t_scene *scene, t_ray ray)
{
	t_intr	intr;
	double	min;
	double	d;
	int		i;
	t_obj	*obj;

	min = __DBL_MAX__;
	obj = NULL;
	i = -1;
	while (++i < scene->obj_num)
	{
		if (scene->obj[i].type == PL)
			d = compute_plane_intersection(ray, scene->obj[i]);
		else if (scene->obj[i].type == SP)
			d = compute_sphere_intersection(ray, scene->obj[i]);
		else
			d = compute_cylinder_intersection(ray, scene->obj[i]);
		register_closest(d, &min, &scene->obj[i], &obj);
	}
	intr.obj = obj;
	if (!obj)
		return (intr);
	intr.position = vectors_point(ray.origin, scale_vector(ray.direction, min));
	return (intr);
}
