/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_vals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:07:46 by asaiz-lo          #+#    #+#             */
/*   Updated: 2025/10/27 16:53:02 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

bool	add_val_am(t_parse *p)
{
	bool	error;

	error = false;
	p->val = get_float(p->tokens[1], &error, 0);
	if (p->val > 1)
		p->val = 1;
	p->c = get_color(p->tokens[2], &error, 0);
	return (error);
}

bool	add_val_cm(t_parse *p)
{
	bool	error;

	error = false;
	p->p = get_point(p->tokens[1], &error, 0);
	p->v = normalize(get_vector(p->tokens[2], &error, 0));
	p->val = (float) ft_atoi(p->tokens[3]);
	if (((int)p->val == 0 && p->tokens[3][0] != '0') || (int)p->val > 180
		|| (int)p->val < 0)
	{
		err(F, Z, (char *[]){"Invalid FOV.\n", NULL});
		error = true;
	}
	return (error);
}

bool	add_val_lg_or_sp(t_parse *p)
{
	bool	error;

	error = false;
	p->p = get_point(p->tokens[1], &error, 0);
	p->val = get_float(p->tokens[2], &error, 0);
	if (p->type == SP)
		p->c = get_color(p->tokens[3], &error, 0);
	else
	{
		if (p->val > 1)
			p->val = 1;
	}
	return (error);
}
// L 46: light dont have light without bonus

bool	add_val_cy_or_pl(t_parse *p)
{
	bool	error;

	error = false;
	p->p = get_point(p->tokens[1], &error, 0);
	p->v = normalize(get_vector(p->tokens[2], &error, 0));
	if (p->type == PL)
	{
		p->c = get_color(p->tokens[3], &error, 0);
	}
	else
	{
		p->val = get_float(p->tokens[3], &error, 0);
		p->height = get_float(p->tokens[4], &error, 0);
		p->c = get_color(p->tokens[5], &error, 0);
	}
	return (error);
}
