/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:14:55 by asaiz-lo          #+#    #+#             */
/*   Updated: 2025/10/27 14:24:32 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

bool	change_cam(t_scene *s)
{
	int		idx;
	bool	err;

	err = false;
	printf("Select the change you want to make:\n");
	printf("\t[1] Change the camera's position by adding {x,y,z}\n");
	printf("\t[2] Change the camera's angle over a plane {x/y/z}\n");
	printf("\t[3] Exit with no change\n");
	idx = get_index();
	if (idx == 1)
	{
		printf("Type the coordinates to sum separated by comas\n");
		s->camera.position = add_points_p(s->camera.position,
				get_point(get_next_line(STDIN_FILENO), &err, 1));
	}
	else if (idx == 2)
		s->camera = get_rotation_cam(s, &err);
	else if (idx == 3)
		err = 0;
	else
		err = 1;
	return (!err);
}

bool	change_light(t_scene *s)
{
	int		idx;
	bool	err;

	idx = -1;
	printf("Select the change you want to make:\n");
	printf("\t[1] Change the lights's position by adding {x,y,z}\n");
	printf("\t[2] Exit with no change\n");
	idx = get_index();
	err = 0;
	if (idx == 1)
	{
		printf("Type the coordinates to sum separated by comas\n");
		s->light.position = add_points_p(s->light.position,
				get_point(get_next_line(STDIN_FILENO), &err, 1));
	}
	else if (idx == 2)
		err = 0;
	else
		err = 1;
	return (!err);
}

bool	change_obj(t_scene *s)
{
	int		idx;
	bool	error;

	idx = 0;
	printf("Select the object:\n");
	while (idx < s->obj_num)
	{
		printf("\t[%i] %s at ", idx + 1, get_type_str(s->obj[idx]));
		print_point(s->obj[idx].position);
		idx++;
	}
	printf("\t[%i] Exit with no change\n", idx + 1);
	idx = get_index();
	if (idx <= s->obj_num && idx > 0)
		error = change_obj_val(s, idx - 1);
	else if (idx == s->obj_num + 1)
		error = 0;
	else
	{
		err(F, Z, (char *[]){" Invalid index.\n", NULL});
		error = 1;
	}
	return (!error);
}

bool	take_input(t_scene *scene)
{
	int		idx;
	bool	check;

	check = false;
	idx = -1;
	printf("Select the change you want to make:\n");
	printf("\t[1] Change the camera\n");
	printf("\t[2] Change the light\n");
	printf("\t[3] Change an object\n");
	printf("\t[4] Exit\n\n");
	idx = get_index();
	if (idx == 1)
		check = change_cam(scene);
	else if (idx == 2)
		check = change_light(scene);
	else if (idx == 3)
		check = change_obj(scene);
	else if (idx == 4)
		check = false;
	else
		printf("Invalid index\n");
	return (check);
}

int	get_index(void)
{
	char	*str;
	int		ret;

	printf("cogiendo input:\n");
	str = get_next_line(STDIN_FILENO);
	ret = 0;
	if (str && str[0])
		ret = ft_atoi(str);
	free(str);
	str = get_next_line(-1);
	return (ret);
}
