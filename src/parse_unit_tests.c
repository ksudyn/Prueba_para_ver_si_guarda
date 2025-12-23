/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_unit_tests.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 12:07:46 by asaiz-lo          #+#    #+#             */
/*   Updated: 2025/11/06 11:26:45 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "../inc/miniRT.h"

void	print_obj(t_obj o)
{
	if (o.type == ER)
		printf("\t\tError\n");
	else if (o.type == SP)
	{
		printf("\t\tpoint = "); print_point(o.position);
		printf("\t\tdiameter = %lf\n", o.diameter); 
		printf("\t\tcolor = "); print_color(o.color);
	}
	else if (o.type == CY)
	{
		printf("\t\tpoint = "); print_point(o.position);
		printf("\t\tdiameter = %lf\n", o.diameter); 
		printf("\t\theight = %lf\n", o.height); 
		printf("\t\tnormal = "); print_vector(o.normal);
		printf("\t\tcolor = "); print_color(o.color);
	}
	else if (o.type == PL)
	{
		printf("\t\tpoint = "); print_point(o.position);
		printf("\t\tnormal = "); print_vector(o.normal);
		printf("\t\tcolor = "); print_color(o.color);
	}
	else
		printf("\t\tError, object type %s as a geometric obj\n",
		 get_type_str(o));
	printf("\n");    
}

void	print_camera(t_camera c)
{
	printf("\t\tstatus = %d\n", c.status);
	printf("\t\tposition = "); print_point(c.position);
	printf("\t\tforward = "); print_vector(c.forward);
	printf("\t\tup = "); print_vector(c.up);
	printf("\t\tright = "); print_vector(c.right);
	printf("\t\tFOV = %lf\n", c.scale);
	printf("\t\tRATIO = %lf\n", c.ratio);
}

void	print_ambient(t_ambient a)
{
	printf("\t\tstatus = %d\n", a.status);
	printf("\t\tbrightness = %lf\n", a.brightness);
	printf("\t\tcolor = "); print_color(a.color);

}

void	print_light(t_light l)
{
	printf("\t\tstatus = %d\n", l.status);
	printf("\t\tposition = "); print_point(l.position);
	printf("\t\tbrightness = %lf\n", l.brightness);
}


void	print_scene(t_scene s)
{
	printf("The scene has been created:\n");
	printf("\tThe camera has been created:\n");
	print_camera(s.camera);

	printf("\tThe ambient has been created:\n");
	print_ambient(s.ambient);

	printf("\tThe light has been created:\n");
	print_light(s.light);
	printf("These are the objects: (Obj_num = %d)\n", s.obj_num);
	for (int i = 0; i < s.obj_num; i++)
	{
		printf("\tThe %s has been created on index [%i]:\n", 
			get_type_str(s.obj[i]), i);
		print_obj(s.obj[i]);
	}    
	printf("\n\n\n");
}/**/
