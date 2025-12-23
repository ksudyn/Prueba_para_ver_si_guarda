/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:44:52 by alvaro            #+#    #+#             */
/*   Updated: 2025/10/20 21:19:00 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

static void	attach_image(t_scene *s)
{
	if (mlx_image_to_window(s->gl.window, s->gl.image, 0, 0) == ERROR)
	{
		mlx_terminate(s->gl.window);
		err(F, Z, (char *[]){ATT_IMG_ERR, NULL});
		exit(EXIT_FAILURE);
	}
}

void	display_image(t_scene *scene)
{
	attach_image(scene);
	mlx_loop(scene->gl.window);
	mlx_terminate(scene->gl.window);
	exit(EXIT_SUCCESS);
}

static void	init_window(t_scene *scene)
{
	scene->gl.window = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	if (scene->gl.window == NULL)
	{
		err(F, Z, (char *[]){INIT_WINDOW_ERR, NULL});
		exit(EXIT_FAILURE);
	}
}

static void	init_image(t_scene *scene)
{
	scene->gl.image = mlx_new_image(scene->gl.window, WIDTH, HEIGHT);
	if (scene->gl.image == NULL)
	{
		mlx_terminate(scene->gl.window);
		err(F, Z, (char *[]){INIT_IMAGE_ERR, NULL});
		exit(EXIT_FAILURE);
	}
}

void	init_graphic_library(t_scene *scene)
{
	init_window(scene);
	init_image(scene);
	mlx_key_hook(scene->gl.window, &key_press, scene);
	mlx_close_hook(scene->gl.window, &cross_click, scene);
}
