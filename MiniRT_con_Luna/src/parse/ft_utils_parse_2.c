/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_parse_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 20:11:58 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/29 19:55:25 by ksudyn           ###   ########.fr       */
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
	ret = (file[i] == '.' && file[i + 1] == 'r' && file[i + 2] == 't' );
	return (ret);
}

// Determina el tipo de objeto

static t_type	get_type_from_token(char *token)
{
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

t_parse	parse_object_type(char *token)
{
	t_parse	parse_data;

	ft_bzero(&parse_data, sizeof(t_parse));
	parse_data.type = get_type_from_token(token);
	return (parse_data);
}

// Crea el objeto en la escena
void	create_scene_object(t_scene *scene, t_parse parse_data)
{
	float	cylinder_data[2];

	if (scene->obj_num >= MAX_OBJ)
		return ;
	if (parse_data.type == CAMERA)
		scene->camera = create_camera(parse_data.p, parse_data.v,
				parse_data.val, true);
	else if (parse_data.type == LIGHT)
		scene->light = create_light(parse_data.val, parse_data.p, true);
	else if (parse_data.type == AMBIENT)
		scene->ambient = create_ambient(parse_data.c, parse_data.val, true);
	else if (parse_data.type == PLANE)
		scene->obj[scene->obj_num++] = create_plane(parse_data.p, parse_data.v,
				parse_data.c);
	else if (parse_data.type == SPHERE)
		scene->obj[scene->obj_num++] = create_sphere(parse_data.p,
				parse_data.val, parse_data.c);
	else if (parse_data.type == CYLINDER)
	{
		cylinder_data[0] = parse_data.val;
		cylinder_data[1] = parse_data.height;
		scene->obj[scene->obj_num++] = create_cylinder(parse_data.p,
				parse_data.v, cylinder_data, parse_data.c);
	}
}
