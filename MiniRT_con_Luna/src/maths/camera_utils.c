/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:48:49 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/29 16:23:25 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static t_vec	get_camera_right(t_vec forward)
{
	t_vec	up;

	up.x = 0;
	up.y = 1;
	up.z = 0;
	if (fabs(scalar_p(forward, up)) > 0.99)
	{
		up.x = 0;
		up.y = 0;
		up.z = 1;
	}
	return (vectorial_p(forward, up));
}

t_camera	create_camera(t_point position, t_vec forward, double fov, bool raw)
{
	t_camera	camera;

	camera.status = true;
	camera.position = position;
	if (is_zero_vector(forward))
		camera.forward = vector_zero();
	else
		camera.forward = normalize(forward);
	camera.scale = fov;
	if (raw)
		camera.scale = tan(fov * PI / 360.0);
	camera.right = get_camera_right(camera.forward);
	camera.up = vectorial_p(camera.right, camera.forward);
	camera.ratio = (double)WIDTH / (double)HEIGHT;
	return (camera);
}
