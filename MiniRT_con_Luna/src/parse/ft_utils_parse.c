/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 20:11:50 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/23 20:16:24 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Asigna valores de ambiente
bool	assign_values_ambient(t_parse *parse)
{
	bool	error;

	error = false;
	parse->val = parse_float(parse->tokens[1], &error, false);
	if (parse->val > 1)
		parse->val = 1;
	parse->c = parse_color(parse->tokens[2], &error, false);
	return (error);
}

// Asigna valores de cámara
bool	assign_values_camera(t_parse *parse)
{
	bool	error;

	error = false;
	parse->p = parse_point(parse->tokens[1], &error, false);
	parse->v = normalize(parse_vector(parse->tokens[2], &error, false));
	parse->val = (float)ft_atoi(parse->tokens[3]);
	if ((parse->val < 0 || parse->val > 180) || ((int)parse->val == 0
			&& parse->tokens[3][0] != '0'))
	{
		ft_error(F, Z, (char *[]){"Invalid FOV.\n", NULL});
		error = true;
	}
	return (error);
}

// Asigna valores para luz o esfera
bool	assign_values_light_or_sphere(t_parse *parse)
{
	bool	error;

	error = false;
	parse->p = parse_point(parse->tokens[1], &error, false);
	parse->val = parse_float(parse->tokens[2], &error, false);
	if (parse->type == SP)
		parse->c = parse_color(parse->tokens[3], &error, false);
	else if (parse->val > 1)
		parse->val = 1;
	return (error);
}

// Asigna valores para cilindro o plano
bool	assign_values_cylinder_or_plane(t_parse *parse)
{
	bool	error;

	error = false;
	parse->p = parse_point(parse->tokens[1], &error, false);
	parse->v = normalize(parse_vector(parse->tokens[2], &error, false));
	if (parse->type == PL)
		parse->c = parse_color(parse->tokens[3], &error, false);
	else
	{
		parse->val = parse_float(parse->tokens[3], &error, false);
		parse->height = parse_float(parse->tokens[4], &error, false);
		parse->c = parse_color(parse->tokens[5], &error, false);
	}
	return (error);
}

// Función genérica que llama a la correcta según tipo
bool	assign_values(t_parse *parse)
{
	if (parse->type == ER)
		return (false);
	else if (parse->type == AM)
		return (assign_values_ambient(parse));
	else if (parse->type == CM)
		return (assign_values_camera(parse));
	else if (parse->type == LG || parse->type == SP)
		return (assign_values_light_or_sphere(parse));
	else if (parse->type == CY || parse->type == PL)
		return (assign_values_cylinder_or_plane(parse));
	return (false);
}
