/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 20:11:50 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/29 18:33:57 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

// Asigna valores de ambiente
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

	parse->c = parse_color(parse->tokens[2], &error, false);
	if (error)
		return (true);
	return (false);
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
	if (parse->type == SPHERE)
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
	parse->v = parse_vector(parse->tokens[2], &error, false);
	if (is_zero_vector(parse->v))
		error = true;
	else
		parse->v = normalize(parse->v);
	if (parse->type == PLANE)
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
