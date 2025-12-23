/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:32:28 by asaiz-lo          #+#    #+#             */
/*   Updated: 2025/10/27 14:53:51 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

char	get_rot_axis(bool *err)
{
	int	idx;

	idx = -1;
	printf("Select the axis to rotate: \n\t[1] x\n\t[2] y\n\t[3] z\n");
	printf("\t[4] Exit\n");
	idx = get_index();
	if (idx == 1)
		return ('x');
	else if (idx == 2)
		return ('y');
	else if (idx == 3)
		return ('z');
	else if (idx == 4)
		return (0);
	*err = 1;
	return (0);
}

t_camera	get_rotation_cam(t_scene *s, bool *err)
{
	t_camera	c;
	t_vec		v;
	char		axis;
	float		angle;

	axis = get_rot_axis(err);
	if (!axis)
		return (s->camera);
	printf("Introduzca el angulo en radianes:\n");
	angle = get_float(get_next_line(STDIN_FILENO), err, 1);
	if (*err)
		return (s->camera);
	v = rotate_vector(s->camera.forward, angle, axis);
	c = create_camera(s->camera.position, v, s->camera.scale, false);
	return (c);
}

t_vec	get_rotation_obj(t_scene *s, int idx, bool *err)
{
	char		axis;
	float		angle;

	axis = get_rot_axis(err);
	if (!axis)
		return (s->obj[idx].normal);
	printf("Introduzca el angulo en radianes:\n");
	angle = get_float(get_next_line(STDIN_FILENO), err, 1);
	if (*err)
	{
		return (s->obj[idx].normal);
	}
	return (rotate_vector(s->obj[idx].normal, angle, axis));
}

t_vec	rotate_vector(t_vec v, float rad, char axis)
{
	t_vec	ret;

	if (axis == 'x')
	{
		ret.x = v.x;
		ret.y = (v.y * cos(rad)) - (v.z * sin(rad));
		ret.z = (v.z * cos(rad)) + (v.y * sin(rad));
	}
	else if (axis == 'y')
	{
		ret.x = (v.x * cos(rad)) + (v.z * sin(rad));
		ret.y = v.y;
		ret.z = (v.z * cos(rad)) - (v.x * sin(rad));
	}
	else if (axis == 'z')
	{
		ret.x = (v.x * cos(rad)) - (v.y * sin(rad));
		ret.y = (v.y * cos(rad)) + (v.x * sin(rad));
		ret.z = v.z;
	}
	else
		return (v);
	return (normalize(ret));
}
