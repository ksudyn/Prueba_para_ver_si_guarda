/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:31:43 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/23 19:57:20 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/miniRT.h"

uint32_t	color_to_int(t_color c)
{
	return (((int)(c.r * 255) << 24)
		| ((int)(c.g * 255) << 16)
		| ((int)(c.b * 255) << 8)
		| OPAQUE);
}

void	put_pixel(t_scene *scene, int x, int y, t_color c)
{
	mlx_put_pixel(scene->gl.image, x, y, color_to_int(c));
}

