/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:30:33 by alvaro            #+#    #+#             */
/*   Updated: 2025/10/27 14:58:30 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

bool	get_vals(char **tokens, t_parse *par)
{
	bool	error;

	error = false;
	par->tokens = tokens;
	if (par->type == ER)
		return (true);
	else if (par->type == AM)
		error = add_val_am(par);
	else if (par->type == CM)
		error = add_val_cm(par);
	else if (par->type == LG || par->type == SP)
		error = add_val_lg_or_sp(par);
	else if (par->type == CY || par->type == PL)
		error = add_val_cy_or_pl(par);
	else
		return (true);
	return (error);
}

// recieves the first token of each line
t_parse	get_type(char *tok)
{
	t_parse		p;

	ft_bzero(&p, sizeof(p));
	if (tok && tok[0])
	{
		if (tok[1] == 0 && tok[0] == 'A')
			p.type = AM;
		else if (tok[1] == 0 && tok[0] == 'C')
			p.type = CM;
		else if (tok[1] == 0 && tok[0] == 'L')
			p.type = LG;
		else if (tok[1] == 0)
			p.type = ER;
		else if (tok[0] == 's' && tok[1] == 'p' && tok[2] == 0)
			p.type = SP;
		else if (tok[0] == 'p' && tok[1] == 'l' && tok[2] == 0)
			p.type = PL;
		else if (tok[0] == 'c' && tok[1] == 'y' && tok[2] == 0)
			p.type = CY;
		else
			p.type = ER;
	}
	return (p);
}

void	create_object(t_scene *s, t_parse p)
{
	float	cyvalh[2];

	if (s->obj_num >= MAX_OBJ)
		return ;
	if (p.type == CM)
		s->camera = create_camera(p.p, p.v, p.val, true);
	else if (p.type == LG)
		s->light = create_light(p.val, p.p, true);
	else if (p.type == AM)
		s->ambient = create_ambient(p.c, p.val, true);
	else if (p.type == PL)
		s->obj[s->obj_num++] = create_plane(p.p, p.v, p.c);
	else if (p.type == SP)
		s->obj[s->obj_num++] = create_sphere(p.p, p.val, p.c);
	else if (p.type == CY)
	{
		cyvalh[0] = p.val;
		cyvalh[1] = p.height;
		s->obj[s->obj_num++] = create_cylinder(p.p, p.v, cyvalh, p.c);
	}
}

bool	parse(char *file, t_scene *s)
{
	int		fd;
	bool	status;

	if (!is_rt(file))
	{
		err(F, Z, (char *[]){"File must be *.rt\n", NULL});
		return (false);
	}
	fd = open(file, O_RDONLY);
	if (!fd)
	{
		err(F, Z, (char *[]){"Could not open the file\n", NULL});
		return (false);
	}
	status = read_file(s, fd);
	if (!s->camera.status)
	{
		err(F, Z, (char *[]){"Camera missing in config.\n", NULL});
		status = false;
	}
	return (status);
}
