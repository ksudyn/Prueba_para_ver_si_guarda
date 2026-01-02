/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:06:58 by ksudyn            #+#    #+#             */
/*   Updated: 2026/01/02 17:53:50 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vec	vectorial_p(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	if (is_zero_vector(result))
		return (vector_zero());
	return (normalize(result));
}

t_vec	add_vectors(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vec	sub_vectors(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vec	scale_vector(t_vec vector, double scale)
{
	vector.x *= scale;
	vector.y *= scale;
	vector.z *= scale;
	return (vector);
}

t_vec	flip_vector(t_vec vector)
{
	vector.x *= -1;
	vector.y *= -1;
	vector.z *= -1;
	return (vector);
}
