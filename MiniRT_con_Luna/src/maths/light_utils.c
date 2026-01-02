/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:49:07 by ksudyn            #+#    #+#             */
/*   Updated: 2026/01/02 17:53:44 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static t_vec	get_plane_normal(t_intr intr, t_ray ray)
{
	if (scalar_p(ray.direction, intr.obj->normal) > 0)
		return (intr.obj->normal);
	return (flip_vector(intr.obj->normal));
}

static t_vec	get_sphere_normal(t_intr intr, t_ray ray)
{
	t_vec	normal;

	normal = sub_points(intr.position, intr.obj->position);
	if (is_zero_vector(normal))
		return (vector_zero());
	normal = normalize(normal);
	if (scalar_p(ray.direction, normal) > 0)
		return (normal);
	return (flip_vector(normal));
}

static t_vec	get_cylinder_normal(t_intr intr, t_ray ray)
{
	t_vec	from_center;
	t_vec	projection;
	double	axial_dot;

	from_center = sub_points(intr.position, intr.obj->position);
	axial_dot = scalar_p(from_center, intr.obj->normal);
	projection = scale_vector(intr.obj->normal, axial_dot);
	from_center = sub_vectors(from_center, projection);
	if (is_zero_vector(from_center))
		return (vector_zero());
	from_center = normalize(from_center);
	if (scalar_p(ray.direction, from_center) > 0)
		return (from_center);
	return (flip_vector(from_center));
}

t_vec	get_normal(t_intr intr, t_ray ray)
{
	if (intr.obj->type == PLANE)
		return (get_plane_normal(intr, ray));
	if (intr.obj->type == SPHERE)
		return (get_sphere_normal(intr, ray));
	if (intr.obj->type == CYLINDER)
		return (get_cylinder_normal(intr, ray));
	return (vector_zero());
}
