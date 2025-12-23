/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:33:34 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/23 19:57:29 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

static bool	is_shadowed(t_scene *scene, t_ray ray, double max_dist)
{
	int		i;
	double	d;

	i = -1;
	while (++i < scene->obj_num)
	{
		if (scene->obj[i].type == PL)
			d = compute_plane_intersection(ray, scene->obj[i]);
		else if (scene->obj[i].type == SP)
			d = compute_sphere_intersection(ray, scene->obj[i]);
		else
			d = compute_cylinder_intersection(ray, scene->obj[i]);
		if (d >= EPSILON && d < max_dist)
			return (true);
	}
	return (false);
}

static t_color	get_diffuse(t_scene *scene, t_intr intr)
{
	t_ray	ray;
	double	intensity;
	t_vec	n;
	double	dist;

	init_shadow_ray(scene->light, &ray, intr);
	n = get_normal(intr, ray);
	ray.origin = vectors_point(ray.origin, scale_vector(n, OFFSET));
	dist = module(sub_points(scene->light.position, intr.position));
	if (is_shadowed(scene, ray, dist))
		return ((t_color){0});
	intensity = fabs(scalar_p(ray.direction, n));
	return ((t_color){
		scene->light.brightness * intensity * intr.obj->color.r,
		scene->light.brightness * intensity * intr.obj->color.g,
		scene->light.brightness * intensity * intr.obj->color.b});
}

static t_color	get_ambient(t_scene *scene, t_intr intr)
{
	if (!scene->ambient.status)
		return ((t_color){0});
	return ((t_color){
		scene->ambient.brightness * scene->ambient.color.r * intr.obj->color.r,
		scene->ambient.brightness * scene->ambient.color.g * intr.obj->color.g,
		scene->ambient.brightness * scene->ambient.color.b * intr.obj->color.b});
}

t_color	get_lighting(t_scene *scene, t_intr intr)
{
	t_color	a;
	t_color	d;

	a = get_ambient(scene, intr);
	d = get_diffuse(scene, intr);
	return ((t_color){
		fmin(a.r + d.r, 1),
		fmin(a.g + d.g, 1),
		fmin(a.b + d.b, 1)});
}
