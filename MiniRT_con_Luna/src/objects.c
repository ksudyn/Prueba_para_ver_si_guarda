/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:31:42 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/23 20:11:33 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_light	create_light(double brightness, t_point position, bool enabled)
{
	t_light	light;

	light.position = position;
	light.brightness = brightness;
	light.status = enabled;
	return (light);
}

t_ambient	create_ambient(t_color color, double brightness, bool enabled)
{
	t_ambient	ambient;

	ambient.color = color;
	ambient.brightness = brightness;
	ambient.status = enabled;
	return (ambient);
}

t_obj	create_plane(t_point position, t_vec normal, t_color color)
{
	t_obj	plane;

	plane.type = PL;
	plane.position = position;
	plane.normal = normalize(normal);
	plane.color = color;
	return (plane);
}

t_obj	create_sphere(t_point position, float radius, t_color color)
{
	t_obj	sphere;

	sphere.type = SP;
	sphere.position = position;
	sphere.diameter = radius * 2.0f;
	sphere.color = color;
	return (sphere);
}

t_obj	create_cylinder(t_point position, t_vec axis,
						float values[2], t_color color)
{
	t_obj	cylinder;

	cylinder.type = CY;
	cylinder.position = position;
	cylinder.normal = normalize(axis);
	cylinder.diameter = values[0] * 2.0f;
	cylinder.height = values[1];
	cylinder.color = color;
	return (cylinder);
}
