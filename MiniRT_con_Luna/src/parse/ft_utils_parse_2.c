/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_parse_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 20:11:58 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/23 20:16:21 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	ret = (file[i] == '.' && file[i + 1] == 'r' && file[i + 2] == 't' );
	return (ret);
}

// Determina el tipo de objeto
t_parse	parse_object_type(char *token)
{
	t_parse	parse_data;

	ft_bzero(&parse_data, sizeof(t_parse));
	if (!token || !token[0])
	{
		parse_data.type = ER;
		return (parse_data);
	}
	if (token[1] == '\0')
	{
		if (token[0] == 'A')
			parse_data.type = AM;
		else if (token[0] == 'C')
			parse_data.type = CM;
		else if (token[0] == 'L')
			parse_data.type = LG;
		else
			parse_data.type = ER;
	}
	else if (ft_strcmp(token, "sp") == 0)
		parse_data.type = SP;
	else if (ft_strcmp(token, "pl") == 0)
		parse_data.type = PL;
	else if (ft_strcmp(token, "cy") == 0)
		parse_data.type = CY;
	else
		parse_data.type = ER;
	return (parse_data);
}

// Crea el objeto en la escena
void	create_scene_object(t_scene *scene, t_parse parse_data)
{
	float	cylinder_data[2];

	if (scene->obj_num >= MAX_OBJ)
		return ;
	if (parse_data.type == CM)
		scene->camera = create_camera(parse_data.p, parse_data.v,
				parse_data.val, true);
	else if (parse_data.type == LG)
		scene->light = create_light(parse_data.val, parse_data.p, true);
	else if (parse_data.type == AM)
		scene->ambient = create_ambient(parse_data.c, parse_data.val, true);
	else if (parse_data.type == PL)
		scene->obj[scene->obj_num++] = create_plane(parse_data.p, parse_data.v,
				parse_data.c);
	else if (parse_data.type == SP)
		scene->obj[scene->obj_num++] = create_sphere(parse_data.p,
				parse_data.val, parse_data.c);
	else if (parse_data.type == CY)
	{
		cylinder_data[0] = parse_data.val;
		cylinder_data[1] = parse_data.height;
		scene->obj[scene->obj_num++] = create_cylinder(parse_data.p,
				parse_data.v, cylinder_data, parse_data.c);
	}
}

t_parse	parse_object_type(char *token)
{
	t_parse	parse_data;

	ft_bzero(&parse_data, sizeof(t_parse));
	parse_data.type = get_type_from_token(token);
	return (parse_data);
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
