/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:33:12 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/23 19:57:24 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

static t_vec	plane_normal(t_intr intr, t_ray ray)
{
	if (scalar_p(ray.direction, intr.obj->normal) > 0)
		return (flip_vector(intr.obj->normal));
	return (intr.obj->normal);
}

static t_vec	sphere_normal(t_intr intr, t_ray ray)
{
	t_vec	n;

	n = normalize(sub_points(intr.position, intr.obj->position));
	if (scalar_p(ray.direction, n) > 0)
		n = flip_vector(n);
	return (n);
}

static t_vec	cylinder_normal(t_intr intr, t_ray ray)
{
	t_vec	op;
	t_vec	proj;
	t_vec	n;

	op = sub_points(intr.position, intr.obj->position);
	proj = scale_vector(intr.obj->normal,
			scalar_p(op, intr.obj->normal));
	n = normalize(sub_vectors(op, proj));
	if (scalar_p(ray.direction, n) > 0)
		n = flip_vector(n);
	return (n);
}

t_vec	get_normal(t_intr intr, t_ray ray)
{
	if (intr.obj->type == PL)
		return (plane_normal(intr, ray));
	if (intr.obj->type == SP)
		return (sphere_normal(intr, ray));
	return (cylinder_normal(intr, ray));
}

