/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_life.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:34:40 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/29 20:15:11 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static bool	check_dup(t_scene *scene, t_type type)
{
	if (type == CAMERA)
		return (!scene->camera.status);
	if (type == AMBIENT)
		return (!scene->ambient.status);
	if (type == LIGHT)
		return (!scene->light.status);
	return (true);
}

static bool	check_type_syntax(t_type type, int count)
{
	if (type == CAMERA)
		return (count == 4);
	if (type == LIGHT)
		return (count == 3);
	if (type == AMBIENT)
		return (count == 3);
	if (type == PLANE)
		return (count == 4);
	if (type == SPHERE)
		return (count == 4);
	if (type == CYLINDER)
		return (count == 6);
	return (false);
}

bool	check_format(t_scene *scene, char **tokens,
		t_type type, bool *error)
{
	int	i;

	if (!tokens)
	{
		ft_error(F, Z, (char *[]){"Split error", NULL});
		*error = true;
		return (false);
	}
	if (!check_dup(scene, type))
	{
		ft_error(F, Z, (char *[]){"Duplicate unique object", NULL});
		*error = true;
		return (false);
	}
	i = 0;
	while (tokens[i])
		i++;
	if (!check_type_syntax(type, i))
	{
		ft_error(F, Z, (char *[]){"Invalid object parameters", NULL});
		*error = true;
		return (false);
	}
	return (true);
}

// Lee el archivo y parsea la escena
bool	read_file(t_scene *scene, int fd)
{
	bool	has_error;
	t_parse	parse_data;
	char	**tokens;

	has_error = false;
	tokens = read_next_line_tokens(fd);
	while (tokens && !has_error)
	{
		if (tokens[0])
		{
			parse_data = parse_object_type(tokens[0]);
			if (check_format(scene, tokens, parse_data.type, &has_error))
			{
				has_error = assign_values(&parse_data);
				if (!has_error)
					create_scene_object(scene, parse_data);
			}
		}
		free_arg(tokens);
		tokens = read_next_line_tokens(fd);
	}
	free_arg(tokens);
	return (!has_error);
}

/*
Ejemplo de cómo cada línea del archivo .rt se convierte en estructuras internas:

Línea del .rt                 Función                        Estructura llenada
--------------------------------------------------------------------------------
A 0.2 255,255,255             		parse_object_type → AMBIENT         scene.ambient
C 0,0,4 0,0,-1 70             		parse_object_type → CAMERA         	scene.camera
L 1,1,1 0.7                    		parse_object_type → LIGH         	scene.light
cy -1,1,-4 0,-1,0 2 2 255,255,0  	parse_object_type → CYLINDER       	scene.obj[]
sp 1,1,-4 2 255,0,0           		parse_object_type → SPHERE         	scene.obj[]
pl 3,2,-5 1,1,0 0,255,0       		parse_object_type → PLANE         	scene.obj[]
pl -2,-2,-2 0,1,0 0,0,255     		parse_object_type → PLANE         	scene.obj[]

Explicación:
- Cada línea se identifica por su primer token (A, C, L, sp, pl, cy).
- parse_object_type() determina el tipo de objeto/luz/cámara.
- Luego, los valores (posición, color, tamaño, normal, etc.) se convierten en números y se guardan
  en la estructura correspondiente dentro de t_scene.
*/
