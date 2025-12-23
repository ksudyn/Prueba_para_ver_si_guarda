/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:18:37 by alvaro            #+#    #+#             */
/*   Updated: 2025/11/06 12:12:00 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	compute_image(t_scene *scene)
{
	t_color	color;
	int		x;
	int		y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = get_pixel_color(scene, x, y);
			put_pixel(scene, x, y, color);
			x++;
		}
		y++;
	}
}

static void	execute(t_scene *scene)
{
	init_graphic_library(scene);
	compute_image(scene);
	display_image(scene);
}

int	main(int ac, char **av)
{
	t_scene		s;

	if (ac != 2)
	{
		err(F, Z, (char *[]){"Bad input\n", NULL});
		return (0);
	}
	else
	{
		ft_bzero(&s, sizeof(s));
		if (!parse(av[1], &s))
		{
			err(F, Z, (char *[]){"Wrong syntax in config file\n", NULL});
			return (1);
		}
		execute(&s);
	}
	return (0);
}
