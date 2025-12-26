/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:07:10 by ksudyn            #+#    #+#             */
/*   Updated: 2025/12/26 15:36:22 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_vec	vector_zero(void)
{
	t_vec	vector;

	vector.x = 0;
	vector.y = 0;
	vector.z = 0;
	return (vector);
}

double	module(t_vec vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y + vector.z
			* vector.z));
}

t_vec	normalize(t_vec vector)
{
	double	magnitude;

	magnitude = module(vector);
	if (magnitude == 0)
		return (vector_zero());
	vector.x /= magnitude;
	vector.y /= magnitude;
	vector.z /= magnitude;
	return (vector);
}

double	scalar_p(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
