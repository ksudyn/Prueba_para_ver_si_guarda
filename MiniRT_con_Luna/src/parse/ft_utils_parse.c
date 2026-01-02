/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 20:11:50 by ksudyn            #+#    #+#             */
/*   Updated: 2026/01/02 16:28:16 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
 * assign_values_ambient(t_parse *parse)
 * ------------------------------------
 * Parsea y asigna los valores de la luz ambiental (A).
 *
 * Formato esperado en el .rt:
 *   A <ratio> <R,G,B>
 *
 * Ejemplo:
 *   A 0.2 255,255,255
 *
 * Cómo funciona:
 * 1. Verifica que la estructura y los tokens existan.
 * 2. Convierte el ratio de iluminación ambiental a float.
 * 3. Limita el ratio al rango [0.0, 1.0].
 * 4. Convierte el color RGB a estructura t_color.
 * 5. Si ocurre cualquier error, devuelve true.
 *
 * Relación con t_scene:
 * - Estos valores se usarán después para crear scene->ambient.
 *
 * Devuelve:
 * - false → todo correcto
 * - true  → error de parseo
 */

bool	assign_values_ambient(t_parse *parse)
{
	bool	error;

	if (!parse || !parse->tokens)
		return (true);
	if (!parse->tokens[1] || !parse->tokens[2])
		return (true);

	error = false;
	parse->val = parse_float(parse->tokens[1], &error, false);
	if (error)
		return (true);
	if (parse->val > 1)
		parse->val = 1;
	if (parse->val < 0)
		parse->val = 0;

	parse->color = parse_color(parse->tokens[2], &error, false);
	if (error)
		return (true);
	return (false);
}

/*
 * assign_values_camera(t_parse *parse)
 * -----------------------------------
 * Parsea y asigna los valores de la cámara (C).
 *
 * Formato esperado en el .rt:
 *   C <x,y,z> <dir_x,dir_y,dir_z> <fov>
 *
 * Ejemplo:
 *   C 0,0,4 0,0,-1 70
 *
 * Cómo funciona:
 * 1. Parsea la posición de la cámara.
 * 2. Parsea el vector de dirección y lo normaliza.
 * 3. Convierte el FOV a entero.
 * 4. Verifica que el FOV esté en el rango [0,180].
 * 5. Si el FOV es inválido, lanza error.
 *
 * Relación con t_scene:
 * - Estos datos se usarán para inicializar scene->camera.
 * - El FOV se utiliza para calcular los rayos del raytracer.
 *
 * Devuelve:
 * - false → cámara válida
 * - true  → error de configuración
 */

bool	assign_values_camera(t_parse *parse)
{
	bool	error;

	error = false;
	parse->point = parse_point(parse->tokens[1], &error, false);
	parse->vec = normalize(parse_vector(parse->tokens[2], &error, false));
	parse->val = (float)ft_atoi(parse->tokens[3]);
	if ((parse->val < 0 || parse->val > 180) || ((int)parse->val == 0
			&& parse->tokens[3][0] != '0'))
	{
		ft_error(F, Z, (char *[]){"Invalid FOV.\n", NULL});
		error = true;
	}
	return (error);
}

/*
 * assign_values_light_or_sphere(t_parse *parse)
 * --------------------------------------------
 * Parsea valores comunes para luz (L) o esfera (sp).
 *
 * Formato esperado:
 *   L  <x,y,z> <brightness>
 *   sp <x,y,z> <diameter> <R,G,B>
 *
 * Ejemplos:
 *   L 1,1,1 0.7
 *   sp 1,1,-4 2 255,0,0
 *
 * Cómo funciona:
 * 1. Parsea la posición (común a ambos).
 * 2. Parsea el valor:
 *    - Para L → brillo
 *    - Para sp → diámetro
 * 3. Si es esfera, parsea el color.
 * 4. Si es luz, limita el brillo al máximo 1.0.
 *
 * Relación con t_scene:
 * - L → scene->light
 * - sp → scene->obj[]
 *
 * Devuelve:
 * - false → valores válidos
 * - true  → error de parseo
 */

bool	assign_values_light_or_sphere(t_parse *parse)
{
	bool	error;

	error = false;
	parse->point = parse_point(parse->tokens[1], &error, false);
	parse->val = parse_float(parse->tokens[2], &error, false);
	if (parse->type == SPHERE)
		parse->color = parse_color(parse->tokens[3], &error, false);
	else if (parse->val > 1)
		parse->val = 1;
	return (error);
}

/*
 * assign_values_cylinder_or_plane(t_parse *parse)
 * ----------------------------------------------
 * Parsea valores comunes para cilindros (cy) y planos (pl).
 *
 * Formato esperado:
 *   pl <point> <normal> <color>
 *   cy <point> <axis> <diameter> <height> <color>
 *
 * Ejemplos:
 *   pl 0,0,-5 0,1,0 255,0,0
 *   cy -1,1,-4 0,-1,0 2 2 255,255,0
 *
 * Cómo funciona:
 * 1. Parsea el punto base del objeto.
 * 2. Parsea el vector normal o eje.
 * 3. Comprueba que el vector no sea nulo.
 * 4. Normaliza el vector.
 * 5. Si es plano:
 *    - Parsea el color.
 * 6. Si es cilindro:
 *    - Parsea diámetro y altura.
 *    - Parsea el color.
 *
 * Relación con t_scene:
 * - Ambos se almacenan en scene->obj[].
 * - El vector normal/eje se usa en intersecciones y normales.
 *
 * Devuelve:
 * - false → correcto
 * - true  → error de parseo
 */

bool	assign_values_cylinder_or_plane(t_parse *parse)
{
	bool	error;

	error = false;
	parse->point = parse_point(parse->tokens[1], &error, false);
	parse->vec = parse_vector(parse->tokens[2], &error, false);
	if (is_zero_vector(parse->vec))
		error = true;
	else
		parse->vec = normalize(parse->vec);
	if (parse->type == PLANE)
		parse->color = parse_color(parse->tokens[3], &error, false);
	else
	{
		parse->val = parse_float(parse->tokens[3], &error, false);
		parse->height = parse_float(parse->tokens[4], &error, false);
		parse->color = parse_color(parse->tokens[5], &error, false);
	}
	return (error);
}

/*
 * assign_values(t_parse *parse)
 * -----------------------------
 * Función central del parseo de valores.
 * Llama a la función específica según el tipo de objeto.
 *
 * Cómo funciona:
 * - Según parse->type, redirige a:
 *     AMBIENT  → assign_values_ambient()
 *     CAMERA   → assign_values_camera()
 *     LIGHT    → assign_values_light_or_sphere()
 *     SPHERE   → assign_values_light_or_sphere()
 *     PLANE    → assign_values_cylinder_or_plane()
 *     CYLINDER → assign_values_cylinder_or_plane()
 *
 * Relación con el flujo:
 * - Se ejecuta después de check_format().
 * - Si esta función falla, el objeto NO se crea.
 *
 * Devuelve:
 * - false → valores correctamente asignados
 * - true  → error durante el parseo
 */

bool	assign_values(t_parse *parse)
{
	if (parse->type == TYPE_ERROR)
		return (false);
	else if (parse->type == AMBIENT)
		return (assign_values_ambient(parse));
	else if (parse->type == CAMERA)
		return (assign_values_camera(parse));
	else if (parse->type == LIGHT || parse->type == SPHERE)
		return (assign_values_light_or_sphere(parse));
	else if (parse->type == CYLINDER || parse->type == PLANE)
		return (assign_values_cylinder_or_plane(parse));
	return (false);
}
