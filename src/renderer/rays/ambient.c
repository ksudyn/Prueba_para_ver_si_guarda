/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-l <dgomez-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:39:19 by asaiz-lo          #+#    #+#             */
/*   Updated: 2025/09/10 12:43:03 by dgomez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

t_color	get_ambient(t_scene *scene, t_intr intrs)
{
	t_color	ambient;

	if (!scene->ambient.status)
		return ((t_color){0});
	ambient.r = scene->ambient.brightness * scene->ambient.color.r
		* intrs.obj->color.r;
	ambient.g = scene->ambient.brightness * scene->ambient.color.g
		* intrs.obj->color.g;
	ambient.b = scene->ambient.brightness * scene->ambient.color.b
		* intrs.obj->color.b;
	return (ambient);
}
