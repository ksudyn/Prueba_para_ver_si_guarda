/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 20:06:41 by ksudyn            #+#    #+#             */
/*   Updated: 2026/02/03 17:30:42 by ksudyn           ###   ########.fr       */
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
	if (keycode == 65307) // ESC
		close_window(scene);
	return (0);
}


int main(int argc, char **argv)
{
    t_scene scene;
    int bits_per_pixel;
    int size_line;
    int endian;

    if (argc != 2)
    {
        printf("Usage: %s <scene.rt>\n", argv[0]);
        return (1);
    }

    // Inicializamos la escena a cero
    ft_memset(&scene, 0, sizeof(t_scene));

    // Parseamos el archivo .rt
    if (!ft_parse(argv[1], &scene))
    {
        printf("Failed to parse scene.\n");
        return (1);
    }

    // Inicializamos MinilibX
    scene.gl.mlx_ptr = mlx_init();
    if (!scene.gl.mlx_ptr)
    {
        printf("Failed to initialize MLX.\n");
        return (1);
    }

    scene.gl.win_ptr = mlx_new_window(scene.gl.mlx_ptr, WIDTH, HEIGHT, "miniRT");
    if (!scene.gl.win_ptr)
    {
        printf("Failed to create MLX window.\n");
        return (1);
    }

    scene.gl.img_ptr = mlx_new_image(scene.gl.mlx_ptr, WIDTH, HEIGHT);
    if (!scene.gl.img_ptr)
    {
        printf("Failed to create MLX image.\n");
        return (1);
    }

    // Obtenemos puntero a los píxeles
    scene.gl.img_data = (int *)mlx_get_data_addr(scene.gl.img_ptr,
                          &bits_per_pixel, &size_line, &endian);
    scene.gl.width = WIDTH;
    scene.gl.height = HEIGHT;

    // Raytracing: dibuja la escena en scene.gl.img_data
    raytrace_scene(&scene);

    // Mostramos imagen en la ventana
    mlx_put_image_to_window(scene.gl.mlx_ptr, scene.gl.win_ptr,
                            scene.gl.img_ptr, 0, 0);

    // 🔑 Hooks IMPORTANTES
	mlx_key_hook(scene.gl.win_ptr, key_press, &scene);          // ESC
	mlx_hook(scene.gl.win_ptr, 17, 0, close_window, &scene);    // ❌                        
    
    // Loop principal de MLX
    mlx_loop(scene.gl.mlx_ptr);

    return (0);
}

//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./miniRT test.rt/nostalgic.rt