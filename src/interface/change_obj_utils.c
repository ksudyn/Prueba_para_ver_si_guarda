/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_obj_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:43:16 by asaiz-lo          #+#    #+#             */
/*   Updated: 2025/10/27 14:50:34 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

bool	change_pl(t_scene *s, int idx)
{
	int		i;
	bool	err;

	err = 0;
	printf("Select the change you want to make:\n");
	printf("\t[1] Change the plane's position by adding {x,y,z}\n");
	printf("\t[2] Rotate the plane\n");
	printf("\t[3] Exit\n\n");
	i = get_index();
	if (i == 1)
	{
		printf("Type the coordinates to sum separated by comas\n");
		s->obj[idx].position = add_points_p(s->obj[idx].position, get_point(
					get_next_line(STDIN_FILENO), &err, 1));
	}
	else if (i == 2)
		s->obj[idx].normal = get_rotation_obj(s, idx, &err);
	else
		err = 0;
	return (err);
}

bool	change_sp(t_scene *s, int idx)
{
	int		i;
	bool	err;

	err = 0;
	printf("Select the change you want to make:\n");
	printf("\t[1] Change the sphere's position by adding {x,y,z}\n");
	printf("\t[2] Exit\n\n");
	i = get_index();
	if (i == 1)
	{
		printf("Type the coordinates to sum separated by comas\n");
		s->obj[idx].position = add_points_p(s->obj[idx].position, get_point(
					get_next_line(STDIN_FILENO), &err, 1));
	}
	else
		err = 0;
	return (err);
}

void	change_cy_aux(t_scene *s, int idx, int i, bool *err)
{
	if (i == 1)
	{
		printf("Type the coordinates to sum separated by comas\n");
		s->obj[idx].position = add_points_p(s->obj[idx].position, get_point(
					get_next_line(STDIN_FILENO), err, 1));
	}
	else if (i == 2)
		s->obj[idx].normal = get_rotation_obj(s, idx, err);
	else if (i == 3)
	{
		printf("Type the new diameter:\n");
		s->obj[idx].diameter = get_float(get_next_line(STDIN_FILENO), err, 1);
	}
	else if (i == 4)
	{
		printf("Type the new height:\n");
		s->obj[idx].height = get_float(get_next_line(STDIN_FILENO), err, 1);
	}
	else
		*err = 0;
}

bool	change_cy(t_scene *s, int idx)
{
	int		i;
	bool	err;

	printf("Select the change you want to make:\n");
	printf("\t[1] Change the cylinder's position by adding {x,y,z}\n");
	printf("\t[2] Rotate the cylinder\n");
	printf("\t[3] Change the cylinder's radious\n");
	printf("\t[4] Change the cylinder's height\n");
	printf("\t[5] Exit\n\n");
	i = get_index();
	err = 0;
	change_cy_aux(s, idx, i, &err);
	return (err);
}

bool	change_obj_val(t_scene *s, int idx)
{
	if (s->obj[idx].type == PL)
		return (change_pl(s, idx));
	else if (s->obj[idx].type == SP)
		return (change_sp(s, idx));
	else if (s->obj[idx].type == CY)
		return (change_cy(s, idx));
	return (0);
}
