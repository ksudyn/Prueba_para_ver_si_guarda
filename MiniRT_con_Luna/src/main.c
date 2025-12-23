/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 20:06:41 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/23 20:07:20 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int main(int argc, char **argv)
{
    t_scene scene;

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

    // Inicializamos MLX42
    scene.gl.window = mlx_init(WIDTH, HEIGHT, "miniRT", false);
    if (!scene.gl.window)
    {
        printf("Failed to initialize MLX window.\n");
        return (1);
    }
    scene.gl.image = mlx_new_image(scene.gl.window, WIDTH, HEIGHT);
    if (!scene.gl.image)
    {
        printf("Failed to create MLX image.\n");
        return (1);
    }

    // Aquí se llamaría a r(scene) para llenar la imagen
    raytrace_scene(&scene);

    // Mostramos imagen
    mlx_image_to_window(scene.gl.window, scene.gl.image, 0, 0);

    // Loop principal de MLX
    mlx_loop(scene.gl.window);

    return (0);
}
