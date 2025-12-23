/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:33:35 by asaiz-lo          #+#    #+#             */
/*   Updated: 2025/10/27 14:44:00 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

char	*get_type_str(t_obj o)
{
	if (o.type == ER)
		return ("Unknown object");
	else if (o.type == PL)
		return ("plane");
	else if (o.type == SP)
		return ("sphere");
	else if (o.type == CY)
		return ("cylinder");
	else if (o.type == CM)
		return ("camera");
	else if (o.type == AM)
		return ("ambient light");
	else if (o.type == LG)
		return ("light");
	return ("Unknown object");
}

void	print_vector(t_vec v)
{
	printf("(x = %f, y = %f, z = %f)\n", v.x, v.y, v.z);
}

void	print_point(t_point p)
{
	printf("(x = %f, y = %f, z = %f)\n", p.x, p.y, p.z);
}

void	print_color(t_color c)
{
	printf("(r = %f, g = %f, b = %f)\n", c.r, c.g, c.b);
}
