/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   difuse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:40:48 by asaiz-lo          #+#    #+#             */
/*   Updated: 2025/09/24 00:18:24 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

void	init_shadow_ray(t_light light, t_ray *ray, t_intr intrs)
{
	ray->origin = intrs.position;
	ray->direction = normalize(sub_points(light.position, intrs.position));
}

double	get_intensity(t_vec direction, t_vec normal)
{
	return (fabs(scalar_p(direction, normal)));
}

t_color	get_diffuse(t_scene *scene, t_intr intrs)
{
	double	intensity;
	t_ray	ray;
	t_color	diffuse;

	init_shadow_ray(scene->light, &ray, intrs);
	intrs.normal = get_normal(intrs, ray);
	ray.origin = vectors_point(ray.origin, scale_vector(intrs.normal, OFFSET));
	if (is_shadowed(scene, ray, intrs))
		return ((t_color){0});
	intensity = get_intensity(ray.direction, intrs.normal);
	diffuse.r = scene->light.brightness * intensity * intrs.obj->color.r;
	diffuse.g = scene->light.brightness * intensity * intrs.obj->color.g;
	diffuse.b = scene->light.brightness * intensity * intrs.obj->color.b;
	return (diffuse);
}
