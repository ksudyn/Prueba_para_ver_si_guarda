/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:32:26 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/26 18:39:36 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	get_ray(t_camera cam, int x, int y)
{
	t_ray	ray;
	double	px;
	double	py;
	t_vec	right;
	t_vec	up;

	px = (2.0 * (x + 0.5) / WIDTH - 1.0) * cam.scale * cam.ratio;
	py = (1.0 - 2.0 * (y + 0.5) / HEIGHT) * cam.scale;
	ray.origin = cam.position;
	right = scale_vector(cam.right, px);
	up = scale_vector(cam.up, py);
	ray.direction = normalize(add_vectors(cam.forward,
				add_vectors(right, up)));
	return (ray);
}

void	init_shadow_ray(t_light light, t_ray *ray, t_intr intr)
{
	ray->origin = intr.position;
	ray->direction = normalize(sub_points(light.position, intr.position));
}

