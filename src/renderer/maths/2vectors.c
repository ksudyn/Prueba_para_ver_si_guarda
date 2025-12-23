/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2vectors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:39:58 by alvaro            #+#    #+#             */
/*   Updated: 2025/09/10 13:20:53 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

double	scalar_p(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	vectorial_p(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (normalize(result));
}

t_vec	add_vectors(t_vec a, t_vec b)
{
	return ((t_vec){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec	sub_vectors(t_vec a, t_vec b)
{
	return ((t_vec){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_point	vectors_point(t_point o, t_vec v)
{
	return ((t_point){o.x + v.x, o.y + v.y, o.z + v.z});
}
