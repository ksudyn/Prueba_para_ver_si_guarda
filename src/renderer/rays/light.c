/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:37:21 by asaiz-lo          #+#    #+#             */
/*   Updated: 2025/09/10 13:24:56 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

static t_color	cap_color(t_color pixel)
{
	if (pixel.r > 1)
		pixel.r = 1;
	if (pixel.g > 1)
		pixel.g = 1;
	if (pixel.b > 1)
		pixel.b = 1;
	return (pixel);
}

static t_color	sum_light(t_color ambient, t_color diffuse)
{
	t_color	pixel;

	pixel.r = ambient.r + diffuse.r;
	pixel.g = ambient.g + diffuse.g;
	pixel.b = ambient.b + diffuse.b;
	pixel = cap_color(pixel);
	return (pixel);
}

t_color	add_light(t_scene *scene, t_intr intr)
{
	t_color	pixel;
	t_color	ambient;
	t_color	diffuse;

	ambient = get_ambient(scene, intr);
	diffuse = get_diffuse(scene, intr);
	pixel = sum_light(ambient, diffuse);
	return (pixel);
}
/* printf("Ambien is %X    ", get_raw(ambient));
	printf("difuse is %X    \n", get_raw(diffuse));*/
