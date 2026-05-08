/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 20:10:56 by ksudyn            #+#    #+#             */
/*   Updated: 2026/01/02 18:34:13 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/*
 * parse_float(char *str, bool *error, bool free_str)
 * --------------------------------------------------
 * Convierte un texto en un número decimal (float).
 *
 * Ejemplo:
 *   "0.2" → 0.2f
 *
 * Cómo funciona:
 * 1. Recorre el string y verifica que solo haya dígitos, puntos o signos (+/-).
 * 2. Si hay algo raro, marca error y devuelve 0.0.
 * 3. Convierte el texto a float usando ft_atolf.
 * 4. Si free_str=true, libera la memoria del string.
 *
 * Uso en el parseo:
 * - Se usa para convertir ratios, diámetros, alturas, FOV, etc.
 */

float	parse_float(char *str, bool *error, bool free_str)
{
	int		i;
	float	result;

	i = 0;
	while (str[i] && !(*error))
	{
		if (!(ft_isdigit(str[i]) || str[i] == '.' || ft_issign(str[i])))
		{
			ft_error(F, Z, (char *[]){"Invalid float format\n", NULL});
			*error = true;
			if (free_str)
				free(str);
			return (0.0f);
		}
		i++;
	}
	result = (float)ft_atolf(str);
	if (free_str)
		free(str);
	return (result);
}

/*
 * parse_int(char *str, bool *error, bool free_str)
 * -----------------------------------------------
 * Convierte un texto en un número entero (int).
 *
 * Ejemplo:
 *   "255" → 255
 *
 * Cómo funciona:
 * 1. Recorre el string y verifica que solo haya dígitos.
 * 2. Si hay algo raro, marca error y devuelve 0.
 * 3. Convierte el texto a int usando ft_atoi.
 * 4. Si free_str=true, libera la memoria del string.
 *
 * Uso en el parseo:
 * - Se usa para colores antes de pasarlos a t_color.
 */

int	parse_int(char *str, bool *error, bool free_str)
{
	int	i;
	int	value;

	i = 0;
	while (str[i] && !(*error))
	{
		if (!ft_isdigit(str[i]))
		{
			ft_error(F, Z, (char *[]){"Invalid int format\n", NULL});
			*error = true;
			if (free_str)
				free(str);
			return (0);
		}
		i++;
	}
	value = ft_atoi(str);
	if (free_str)
		free(str);
	return (value);
}

/*
 * parse_point(char *str, bool *error, bool free_str)
 * --------------------------------------------------
 * Convierte un texto con formato "x,y,z" en un punto 3D (t_point).
 *
 * Ejemplo:
 *   "0,0,4" → t_point {x=0, y=0, z=4}
 *
 * Cómo funciona:
 * 1. Divide el string por comas usando ft_split.
 * 2. Verifica que haya exactamente 3 partes.
 * 3. Convierte cada parte a float usando parse_float.
 * 4. Libera memoria de componentes y del string si free_str=true.
 *
 * Uso en el parseo:
 * - Se usa para la posición de cámara, luces y objetos.
 */

t_point	parse_point(char *str, bool *error, bool free_str)
{
	char	**components;
	t_point	point;

	components = ft_split(str, ',');
	ft_memset(&point, 0, sizeof(t_point));
	if (!components || ft_arr_len(components) != 3)
		return (free_arg(components), *error = true, point);
	point.x = parse_float(components[0], error, false);
	point.y = parse_float(components[1], error, false);
	point.z = parse_float(components[2], error, false);
	free_arg(components);
	if (free_str)
		free(str);
	return (point);
}

/*
 * parse_vector(char *str, bool *error, bool free_str)
 * --------------------------------------------------
 * Convierte un texto "x,y,z" en un vector 3D (t_vec).
 *
 * Ejemplo:
 *   "0,0,-1" → t_vec {x=0, y=0, z=-1}
 *
 * Cómo funciona:
 * 1. Divide el string por comas.
 * 2. Verifica que haya exactamente 3 partes.
 * 3. Convierte cada parte a float.
 * 4. Si el vector es {0,0,0}, marca error.
 * 5. Libera memoria de componentes y del string si free_str=true.
 *
 * Uso en el parseo:
 * - Se usa para la dirección de cámara, normal de planos, eje de cilindros.
 */

t_vec	parse_vector(char *str, bool *error, bool free_str)
{
	t_vec	vector;
	char	**components;

	ft_memset(&vector, 0, sizeof(t_vec));
	components = ft_split(str, ',');
	if (!components || ft_arr_len(components) != 3)
		return (free_arg(components), *error = true, vector);
	vector.x = parse_float(components[0], error, false);
	vector.y = parse_float(components[1], error, false);
	vector.z = parse_float(components[2], error, false);
	if (is_zero_vector(vector))
		*error = true;
	free_arg(components);
	if (free_str)
		free(str);
	return (vector);
}

/*
 * parse_color(char *str, bool *error, bool free_str)
 * --------------------------------------------------
 * Convierte un texto "R,G,B" en un color (t_color) con valores entre 0 y 1.
 *
 * Ejemplo:
 *   "255,0,0" → t_color {r=1.0, g=0.0, b=0.0}
 *
 * Cómo funciona:
 * 1. Divide el string por comas.
 * 2. Verifica que haya exactamente 3 partes.
 * 3. Convierte cada parte a int usando parse_int.
 * 4. Divide entre 255 para que quede entre 0 y 1.
 * 5. Libera memoria de componentes y del string si free_str=true.
 *
 * Uso en el parseo:
 * - Se usa para color de luces y objetos.
 */

t_color	parse_color(char *str, bool *error, bool free_str)
{
	t_color	color;
	char	**components;

	ft_memset(&color, 0, sizeof(t_color));
	components = ft_split(str, ',');
	if (!components || ft_arr_len(components) != 3)
		return (free_arg(components), *error = true, color);
	color.r = parse_int(components[0], error, false) / 255.0;
	color.g = parse_int(components[1], error, false) / 255.0;
	color.b = parse_int(components[2], error, false) / 255.0;
	free_arg(components);
	if (free_str)
		free(str);
	return (color);
}
