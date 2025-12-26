/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_life.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:34:40 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/26 19:07:43 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static bool	check_dup(t_scene *scene, t_type type)
{
	if (type == CM)
		return (!scene->camera.status);
	if (type == AM)
		return (!scene->ambient.status);
	if (type == LG)
		return (!scene->light.status);
	return (true);
}

static bool	check_type_syntax(t_type type, int count)
{
	if (type == CM)
		return (count == 4);
	if (type == LG)
		return (count == 3);
	if (type == AM)
		return (count == 3);
	if (type == PL)
		return (count == 4);
	if (type == SP)
		return (count == 4);
	if (type == CY)
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

// bool	read_file(t_scene *scene, int fd)
// {
// 	bool	has_error;
// 	t_parse	parse_data;
// 	char	**tokens;

// 	has_error = false;
// 	tokens = read_next_line_tokens(fd);
// 	while (tokens && !has_error)
// 	{
// 		if (tokens[0])
// 		{
// 			parse_data = parse_object_type(tokens[0]);
// 			parse_data.tokens = tokens;
// 			if (check_format(scene, tokens, parse_data.type, &has_error))
// 			{
// 				has_error = assign_values(&parse_data);
// 				if (!has_error)
// 					create_scene_object(scene, parse_data);
// 			}
// 		}
// 		free_arg(tokens);
// 		tokens = read_next_line_tokens(fd);
// 	}
// 	free_arg(tokens);
// 	return (!has_error);
// }

//Ya estan en ft_utils_parse_2.c