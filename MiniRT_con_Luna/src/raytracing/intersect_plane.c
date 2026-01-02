/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:54:19 by ksudyn            #+#    #+#             */
/*   Updated: 2026/01/02 17:53:21 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	compute_plane_intersection(t_ray ray, t_obj obj)
{
	double	denom;
	double	t;
	t_vec	p0l0;

	denom = scalar_p(obj.normal, ray.direction);
	if (fabs(denom) < EPSILON)
		return (NOINTERSECTION);
	p0l0 = sub_points(obj.position, ray.origin);
	t = scalar_p(p0l0, obj.normal) / denom;
	if (t > EPSILON)
		return (t);
	return (NOINTERSECTION);
}
