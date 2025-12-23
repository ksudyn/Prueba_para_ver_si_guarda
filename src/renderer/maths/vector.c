/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:24:44 by alvaro            #+#    #+#             */
/*   Updated: 2025/09/29 11:40:07 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

double	module(t_vec vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y + vector.z
			* vector.z));
}

t_vec	normalize(t_vec vector)
{
	double	mag;

	mag = module(vector);
	return ((t_vec){vector.x / mag, vector.y / mag, vector.z / mag});
}

t_vec	scale_vector(t_vec vector, double scale)
{
	return ((t_vec){vector.x * scale, vector.y * scale, vector.z * scale});
}

t_vec	flip_vector(t_vec vector)
{
	return ((t_vec){vector.x * -1, vector.y * -1, vector.z * -1});
}
