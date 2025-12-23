/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:49:23 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/23 20:14:56 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	sub_points(t_point a, t_point b)
{
	t_vec	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_point	vectors_point(t_point origin, t_vec vector)
{
	t_point	result;

	result.x = origin.x + vector.x;
	result.y = origin.y + vector.y;
	result.z = origin.z + vector.z;
	return (result);
}

double	euclidean_distance(t_point a, t_point b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) + (b.z
				- a.z) * (b.z - a.z)));
}
