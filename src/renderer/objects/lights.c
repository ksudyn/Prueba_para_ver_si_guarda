/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 23:33:18 by marvin            #+#    #+#             */
/*   Updated: 2025/12/22 15:14:16 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

t_light	create_light(double brightness, t_point pos, bool on)
{
	t_light		l;

	l.position = pos;
	l.brightness = brightness;
	l.status = on;
	return (l);
}

t_ambient	create_ambient(t_color c, double brightness, bool on)
{
	t_ambient	a;

	a.color = c;
	a.brightness = brightness;
	a.status = on;
	return (a);}
