/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:31:43 by ksudyn            #+#    #+#             */
/*   Updated: 2026/05/07 19:04:19 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
 * color_to_int()
 * --------------
 * Convierte el formato de color RGB a un entero (Hexadecimal).
 * * Por qué es necesario:
 * - Trabajamos con tres valores (R, G, B) de 0.0 a 1.0 para los cálculos.
 * - La MiniLibX necesita un solo número entero (como 0xFFFFFF)
 * 		para pintar el píxel.
 * - Esta función "empaqueta" los tres colores en un solo `int`
 * 		usando desplazamientos de bits.
 */
int	color_to_int(t_color c)
{
	return ((int)(c.r * 255) << 16 | (int)(c.g * 255) << 8 | (int)(c.b * 255));
}

/*
 * put_pixel()
 * -----------
 * Dibuja un color en una coordenada específica de la imagen.
 * * Cómo funciona:
 * - Convierte el color a formato entero.
 * - Verifica que el píxel esté dentro de los límites de la ventana
 * 		(para evitar Segfaults).
 * - Guarda el color en el array de datos de la imagen de MiniLibX.
 */
void	put_pixel(t_scene *scene, int x, int y, t_color c)
{
	int	color;

	color = color_to_int(c);
	if (x < 0 || x >= scene->gl.width || y < 0 || y >= scene->gl.height)
		return ;
	scene->gl.img_data[y * scene->gl.width + x] = color;
}
