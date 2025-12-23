/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:33:13 by asaiz-lo          #+#    #+#             */
/*   Updated: 2025/10/27 15:31:57 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

bool	check_zero_vector(t_vec v, bool *error)
{
	bool	tmp;

	tmp = (fabs(v.x) < EPSILON && fabs(v.y) < EPSILON && fabs(v.z) < EPSILON);
	if (tmp)
		err("get_vars.c", 117, (char *[]){"Zero vector detected.\n", NULL});
	*error = tmp;
	return (*error);
}

bool	is_rt(char *file)
{
	int		i;
	bool	ret;

	if (ft_strrchr(file, '/'))
		file = ft_strrchr(file, '/') + 1;
	if (!file || ft_strlen(file) <= 3)
		return (false);
	i = 0;
	while (file[i + 3])
		i++;
	ret = (file[i] == '.' && file[i + 1] == 'r' && file[i + 2] == 't' );
	return (ret);
}

static bool	check_dup(t_scene *s, t_type type)
{
	if (type == CM)
		return (!s->camera.status);
	if (type == AM)
		return (!s->ambient.status);
	if (type == LG)
		return (!s->light.status);
	return (true);
}

static bool	check_type_syntax(t_type type, int i)
{
	if (type == CM)
		return (i == 4);
	else if (type == LG)
		return (i == 3);
	else if (type == AM)
		return (i == 3);
	else if (type == PL)
		return (i == 4);
	else if (type == SP)
		return (i == 4);
	else if (type == CY)
		return (i == 6);
	return (false);
}

//  No repeated and correct args for type
bool	check_format(t_scene *s, char **toks, t_type type, bool *error)
{
	int		i;
	t_obj	o;

	if (!toks)
	{
		err(F, Z, (char *[]){"Split error.\n", NULL});
		return (false);
	}
	if (!check_dup(s, type))
	{
		err(F, Z, (char *[]){"Duplicate unique object.\n", NULL});
		return (*error = true, false);
	}
	i = 0;
	while (toks[i])
		i++;
	if (!check_type_syntax(type, i))
	{
		o.type = type;
		err(F, Z, (char *[]){get_type_str(o),
			" has invalid parameters.\n", NULL});
		return (*error = true, false);
	}
	return (true);
}
