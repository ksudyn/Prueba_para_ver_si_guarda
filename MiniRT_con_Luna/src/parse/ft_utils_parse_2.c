/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_parse_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 20:11:58 by ksudyn            #+#    #+#             */
/*   Updated: 2026/01/02 18:18:05 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

bool	is_rt(char *file)
{
	int		i;
	bool	ret;

	if (ft_strrchr(file, '/'))
		file = ft_strrchr(file, '/') + 1;
	if (!file || ft_strlen(file) <= 3)
		return (false);
	i = 0;
	while (file[i + 3])
		i++;
	ret = (file[i] == '.' && file[i + 1] == 'r' && file[i + 2] == 't');
	return (ret);
}

/*
 * get_type_from_token(char *token)
 * --------------------------------

 * Determina el tipo de elemento de la escena a partir del primer token de una línea.
 *
 * Parámetro:
 *
	- token: primer elemento de la línea del archivo .rt (identificador del objeto)
 *
 * Cómo funciona:
 * 1. Si el token es NULL o vacío, devuelve TYPE_ERROR.
 * 2. Si el token tiene un solo carácter:
 *    - 'A' → luz ambiental (AMBIENT)
 *    - 'C' → cámara (CAMERA)
 *    - 'L' → luz puntual (LIGHT)
 * 3. Si el token tiene dos caracteres:
 *    - "sp" → esfera (SPHERE)
 *    - "pl" → plano (PLANE)
 *    - "cy" → cilindro (CYLINDER)
 * 4. Si no coincide con ninguno, devuelve TYPE_ERROR.
 *
 * Relación con el archivo .rt:
 * - Identifica qué tipo de línea se está parseando:
 *     "A 0.2 255,255,255"        → AMBIENT
 *     "C 0,0,4 0,0,-1 70"        → CAMERA
 *     "L 1,1,1 0.7"              → LIGHT
 *     "sp 1,1,-4 2 255,0,0"      → SPHERE
 *     "pl 0,0,-5 0,1,0 255,255,0"→ PLANE
 *     "cy -1,1,-4 0,-1,0 2 2 ..."→ CYLINDER
 *
 * Esta función NO parsea valores numéricos, solo identifica el tipo de objeto.
 */

static t_type	get_type_from_token(char *token)
{
	//printf("DEBUG get_type_from_token: token='%s'\n", token);
	if (!token || !token[0])
		return (TYPE_ERROR);
	if (token[1] == '\0')
	{
		if (token[0] == 'A')
			return (AMBIENT);
		if (token[0] == 'C')
			return (CAMERA);
		if (token[0] == 'L')
			return (LIGHT);
		return (TYPE_ERROR);
	}
	if (ft_strcmp(token, "sp") == 0)
		return (SPHERE);
	if (ft_strcmp(token, "pl") == 0)
		return (PLANE);
	if (ft_strcmp(token, "cy") == 0)
		return (CYLINDER);
	return (TYPE_ERROR);
}

/*
 * parse_object_type(char *token)
 * --------------------------------
 * Inicializa una estructura t_parse y asigna el tipo del objeto
 * según el identificador leído del archivo .rt.
 *
 * Parámetro:
 * - token: primer token de la línea (identificador del objeto)
 *
 * Cómo funciona:
 * 1. Inicializa toda la estructura t_parse a cero con ft_bzero.
 * 2. Obtiene el tipo del objeto llamando a get_type_from_token().
 * 3. Guarda el tipo en parse_data.type.
 * 4. Devuelve la estructura inicializada.
 *
 * Relación con el archivo .rt:
 * - Cada línea del archivo crea un t_parse temporal:
 *     tokens[0] = "sp" → parse_data.type = SPHERE
 *     tokens[0] = "A"  → parse_data.type = AMBIENT
 *
 * Esta estructura se completa más adelante con:
 * - posiciones
 * - vectores
 * - colores
 * - valores numéricos
 */

t_parse	parse_object_type(char *token)
{
	t_parse	parse_data;

	ft_bzero(&parse_data, sizeof(t_parse));
	parse_data.type = get_type_from_token(token);
	return (parse_data);
}

/*
 * add_camera(t_scene *scene, t_parse parse_data)
 * ---------------------------------------------
 * Añade la cámara parseada a la escena.
 *
 * Cómo funciona:
 * - Llama a create_camera() con los datos parseados.
 * - Marca camera.status = true
 *
 * Relación con el flujo:
 * - Llamado desde create_scene_object() cuando parse_data.type == CAMERA
 */

static void	add_camera(t_scene *scene, t_parse parse_data)
{
	scene->camera = create_camera(parse_data.point, parse_data.vec,
			parse_data.val, true);
	scene->camera.status = true;
}

/*
 * create_scene_object(t_scene *scene, t_parse parse_data)
 * -------------------------------------------------------
 * Función central que inserta un objeto o luz/cámara en la escena.
 *
 * Cómo funciona:
 * 1. Si el número de objetos >= MAX_OBJ, retorna sin hacer nada.
 * 2. Según parse_data.type:
 *    - CAMERA  → add_camera()
 *    - LIGHT   → create_light() → scene->light
 *    - AMBIENT → create_ambient() → scene->ambient
 *    - PLANE   → create_plane() → scene->obj[]
 *    - SPHERE  → create_sphere() → scene->obj[]
 *    - CYLINDER→ create_cylinder() → scene->obj[]
 * 3. Para cilindro usa un array temporal cylinder_data[2] = {diameter, height}
 * 4. Incrementa scene->obj_num solo para objetos que se almacenan en obj[]
 *
 * Relación con .rt:
 * - Cada línea del archivo, tras parsear y asignar valores, termina aquí
 *   para convertirse en parte de la escena que se dibujará.
 */

void	create_scene_object(t_scene *scene, t_parse parse_data)
{
	float	cylinder_data[2];

	if (scene->obj_num >= MAX_OBJ)
		return ;
	if (parse_data.type == CAMERA)
		add_camera(scene, parse_data);
	else if (parse_data.type == LIGHT)
		scene->light = create_light(parse_data.val, parse_data.point, true);
	else if (parse_data.type == AMBIENT)
		scene->ambient = create_ambient(parse_data.color, parse_data.val, true);
	else if (parse_data.type == PLANE)
		scene->obj[scene->obj_num++] = create_plane(parse_data.point,
				parse_data.vec, parse_data.color);
	else if (parse_data.type == SPHERE)
		scene->obj[scene->obj_num++] = create_sphere(parse_data.point,
				parse_data.val, parse_data.color);
	else if (parse_data.type == CYLINDER)
	{
		cylinder_data[0] = parse_data.val;
		cylinder_data[1] = parse_data.height;
		scene->obj[scene->obj_num++] = create_cylinder(parse_data.point,
				parse_data.vec, cylinder_data, parse_data.color);
	}
}
