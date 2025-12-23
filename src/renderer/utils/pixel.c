/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:23:35 by asaiz-lo          #+#    #+#             */
/*   Updated: 2025/09/10 14:18:03 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

static bool	is_miss(t_intr intr)
{
	return (intr.obj == NULL);
}

t_color	get_pixel_color(t_scene *scene, int x, int y)
{
	t_ray	ray;
	t_intr	intr;
	t_color	pixel;

	ray = get_ray(scene->camera, x, y);
	intr = get_intr(scene, ray);
	if (is_miss(intr))
		return ((t_color){0, 0, 0});
	pixel = add_light(scene, intr);
	return (pixel);
}
