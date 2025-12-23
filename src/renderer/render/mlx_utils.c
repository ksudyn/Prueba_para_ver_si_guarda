/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:24:43 by alvaro            #+#    #+#             */
/*   Updated: 2025/10/27 15:08:06 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

void	key_press(mlx_key_data_t keycode, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keycode.action == MLX_PRESS || keycode.action == MLX_REPEAT)
	{
		if (keycode.key == 256)
			mlx_close_window(scene->gl.window);
		if (keycode.key == 69)
		{
			take_input(scene);
			compute_image(scene);
			display_image(scene);
		}
	}
}

void	cross_click(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	mlx_close_window(scene->gl.window);
}

uint32_t	get_raw(t_color color)
{
	return (((int)round(color.r * 255.0) << 24) | ((int)round(color.g
				* 255.0) << 16) | ((int)round(color.b * 255.0) << 8) | OPAQUE);
}

void	put_pixel(t_scene *scene, int x, int y, t_color color)
{
	mlx_put_pixel(scene->gl.image, x, y, get_raw(color));
}
