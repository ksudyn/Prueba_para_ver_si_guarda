/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:31:43 by ksudyn            #+#    #+#             */
/*   Updated: 2026/01/02 17:53:05 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	color_to_int(t_color c)
{
	return ((int)(c.r * 255) << 16 | (int)(c.g * 255) << 8 | (int)(c.b * 255));
}

void	put_pixel(t_scene *scene, int x, int y, t_color c)
{
	int	color;

	color = color_to_int(c);
	if (x < 0 || x >= scene->gl.width || y < 0 || y >= scene->gl.height)
		return ;
	scene->gl.img_data[y * scene->gl.width + x] = color;
}
