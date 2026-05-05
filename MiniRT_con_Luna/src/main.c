/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 20:06:41 by ksudyn            #+#    #+#             */
/*   Updated: 2026/05/05 17:45:50 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	close_window(t_scene *scene)
{
	if (!scene)
		return (0);
	mlx_destroy_image(scene->gl.mlx_ptr, scene->gl.img_ptr);
	mlx_destroy_window(scene->gl.mlx_ptr, scene->gl.win_ptr);
	mlx_destroy_display(scene->gl.mlx_ptr);
	free(scene->gl.mlx_ptr);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_scene *scene)
{
	if (keycode == 65307)
		close_window(scene);
	return (0);
}

static int	init_mlx(t_scene *scene)
{
	int	bits_per_pixel;
	int	size_line;
	int	endian;

	scene->gl.mlx_ptr = mlx_init();
	if (!scene->gl.mlx_ptr)
		return (printf("Failed to initialize MLX.\n"), 0);
	scene->gl.win_ptr = mlx_new_window(scene->gl.mlx_ptr, WIDTH, HEIGHT,
			"miniRT");
	if (!scene->gl.win_ptr)
		return (printf("Failed to create MLX window.\n"), 0);
	scene->gl.img_ptr = mlx_new_image(scene->gl.mlx_ptr, WIDTH, HEIGHT);
	if (!scene->gl.img_ptr)
		return (printf("Failed to create MLX image.\n"), 0);
	scene->gl.img_data = (int *)mlx_get_data_addr(scene->gl.img_ptr,
			&bits_per_pixel, &size_line, &endian);
	scene->gl.width = WIDTH;
	scene->gl.height = HEIGHT;
	return (1);
}

static void	init_hooks(t_scene *scene)
{
	mlx_key_hook(scene->gl.win_ptr, key_press, scene);
	mlx_hook(scene->gl.win_ptr, 17, 0, close_window, scene);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
		return (printf("Usage: %s <scene.rt>\n", argv[0]), 1);
	ft_memset(&scene, 0, sizeof(t_scene));
	if (!ft_parse(argv[1], &scene))
		return (printf("Failed to parse scene.\n"), 1);
	if (!init_mlx(&scene))
		return (1);
	raytrace_scene(&scene);
	mlx_put_image_to_window(scene.gl.mlx_ptr, scene.gl.win_ptr,
		scene.gl.img_ptr, 0, 0);
	init_hooks(&scene);
	mlx_loop(scene.gl.mlx_ptr);
	return (0);
}

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./miniRT test.rt/nostalgic.rt