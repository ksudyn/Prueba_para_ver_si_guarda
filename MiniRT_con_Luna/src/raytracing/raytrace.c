/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:34:05 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/26 18:39:25 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	raytrace_scene(t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	t_intr	intr;
	t_color	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = get_ray(scene->camera, x, y);
			intr = get_intersection(scene, ray);
			if (intr.obj)
				color = get_lighting(scene, intr);
			else
				color = (t_color){0};
			put_pixel(scene, x, y, color);
			x++;
		}
		y++;
	}
}
