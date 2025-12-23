/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:24:41 by asaiz-lo          #+#    #+#             */
/*   Updated: 2025/09/10 13:20:53 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

// func to adjust normal's orientation
static t_vec	get_obj_normal(t_intr intr, t_ray ray)
{
	t_vec	normal;

	if (scalar_p(ray.direction, intr.obj->normal) > 0)
		normal = intr.obj->normal;
	else
		normal = flip_vector(intr.obj->normal);
	return (normal);
}

static t_vec	get_sphere_normal(t_intr intr, t_ray ray)
{
	t_vec	normal;
	t_vec	vec_from_obj_center_to_intr;

	vec_from_obj_center_to_intr = sub_points(intr.position, intr.obj->position);
	vec_from_obj_center_to_intr = normalize(vec_from_obj_center_to_intr);
	if (scalar_p(ray.direction, vec_from_obj_center_to_intr) > 0)
		normal = vec_from_obj_center_to_intr;
	else
		normal = flip_vector(vec_from_obj_center_to_intr);
	return (normal);
}

static t_vec	get_cylinder_normal(t_intr intr, t_ray ray)
{
	t_vec		normal;
	t_vec		vec_from_obj_center_to_intr;
	t_vec		proj_on_axis;
	double		dot_product_axial;

	vec_from_obj_center_to_intr = sub_points(intr.position, intr.obj->position);
	dot_product_axial = scalar_p(vec_from_obj_center_to_intr,
			intr.obj->normal);
	proj_on_axis = scale_vector(intr.obj->normal, dot_product_axial);
	normal = sub_vectors(vec_from_obj_center_to_intr, proj_on_axis);
	normal = normalize(normal);
	if (scalar_p(ray.direction, normal) > 0)
		normal = flip_vector(normal);
	return (flip_vector(normal));
}

t_vec	get_normal(t_intr intr, t_ray ray)
{
	if (intr.obj->type == PL)
		return (get_obj_normal(intr, ray));
	else if (intr.obj->type == SP)
		return (get_sphere_normal(intr, ray));
	else if (intr.obj->type == CY)
		return (get_cylinder_normal(intr, ray));
	return ((t_vec){0});
}
