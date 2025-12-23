/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:56:15 by asaiz-lo          #+#    #+#             */
/*   Updated: 2025/09/29 11:40:37 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

t_vec	sub_points(t_point a, t_point b)
{
	return ((t_vec){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_point	add_points_p(t_point a, t_point b)
{
	return ((t_point){a.x + b.x, a.y + b.y, a.z + b.z});
}

double	euclidean_distance(t_point a, t_point b)
{
	double		ret;

	ret = (b.x - a.x) * (b.x - a.x);
	ret += (b.y - a.y) * (b.y - a.y);
	ret += (b.z - a.z) * (b.z - a.z);
	ret = sqrt(ret);
	return (ret);
}
