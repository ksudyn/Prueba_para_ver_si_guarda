/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 23:31:21 by marvin            #+#    #+#             */
/*   Updated: 2025/10/27 16:59:43 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

// if the projection of forward over the assumed "up" is too similar 
// (almost paralel), we asume other "upward direction"
static t_vec	get_right(t_vec forward)
{
	t_vec		tmp_up;

	tmp_up = (t_vec){0, 1, 0};
	if (fabs (scalar_p(forward, tmp_up)) > 0.99)
		tmp_up = (t_vec){0, 0, 1};
	return (vectorial_p(forward, tmp_up));
}

t_camera	create_camera(t_point pos, t_vec forw, double fov, bool raw)
{
	t_camera	camera;

	camera.status = true;
	camera.position = pos;
	camera.forward = forw;
	camera.scale = fov;
	if (raw)
		camera.scale = tan(fov * PI / 360);
	camera.right = get_right(forw);
	camera.up = vectorial_p(camera.right, camera.forward);
	camera.ratio = (double)WIDTH / (double)HEIGHT;
	return (camera);
}
