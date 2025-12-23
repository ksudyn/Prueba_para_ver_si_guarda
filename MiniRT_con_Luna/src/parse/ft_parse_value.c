/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 20:10:56 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/23 20:16:14 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Convierte string a float
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

// Convierte string a int
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

// Convierte string a punto
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

// Convierte string a vector
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
	if (check_zero_vector(vector, error))
		vector = (t_vec){0, 0, 0};
	free_arg(components);
	if (free_str)
		free(str);
	return (vector);
}

// Convierte string a color
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
