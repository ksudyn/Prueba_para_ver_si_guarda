/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaiz-lo <asaiz-lo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:04:11 by asaiz-lo          #+#    #+#             */
/*   Updated: 2025/11/06 11:58:29 by asaiz-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

float	get_float(char *str, bool *error, bool reserved)
{
	float	f;
	int		i;

	i = ft_strlen(str);
	if (str[i - 1] == '\n')
		str[i - 1] = 0;
	i = 0;
	while (str[i] && !(*error))
	{
		if (!(str[i] == '.' || ft_isdigit(str[i]) || ft_issign(str[i])))
		{
			if (ft_strrchr(str, '\n'))
				*ft_strrchr(str, '\n') = '\0';
			err(F, Z, (char *[]){"{", str, "}", " Invalid float format.\n",
				NULL});
			if (reserved)
				free(str);
			return (*error = true, (float) 0.0);
		}
		i++;
	}
	f = ft_atolf(str);
	if (reserved)
		free(str);
	return (f);
}

int	get_int(char *str, bool *error, bool reserved)
{
	int		ret;
	int		i;

	i = ft_strlen(str);
	if (str[i - 1] == '\n')
		str[i - 1] = 0;
	i = 0;
	while (str[i] && !(*error))
	{
		if (!ft_isdigit(str[i]))
		{
			if (ft_strrchr(str, '\n'))
				*ft_strrchr(str, '\n') = '\0';
			err(F, Z, (char *[]){"{", str, "}", " Invalid int format.\n",
				NULL});
			if (reserved)
				free(str);
			return (*error = true, 0);
		}
		i++;
	}
	ret = ft_atoi(str);
	if (reserved)
		free(str);
	return (ret);
}

t_point	get_point(char *str, bool *error, bool reserved)
{
	t_point		p;
	int			i;
	char		**arr;

	arr = ft_split(str, ',');
	i = 0;
	while (arr[i])
		i++;
	if (i != 3)
	{
		if (ft_strrchr(str, '\n'))
			*ft_strrchr(str, '\n') = '\0';
		err(F, Z, (char *[]){"{", str, "}", " Invalid point format.\n", NULL});
		if (reserved)
			free(str);
		return (free_arr(arr), *error = true, (t_point){0, 0, 0});
	}
	p.x = get_float(arr[0], error, 0);
	p.y = get_float(arr[1], error, 0);
	p.z = get_float(arr[2], error, 0);
	if (reserved)
		free(str);
	if (*error)
		return (free_arr(arr), (t_point){0, 0, 0});
	return (free_arr(arr), p);
}

t_vec	get_vector(char *str, bool *error, bool reserved)
{
	t_vec		v;
	int			i;
	char		**arr;

	arr = ft_split(str, ',');
	i = 0;
	while (arr[0] && arr[i])
		i++;
	if (i != 3)
	{
		if (ft_strrchr(str, '\n'))
			*ft_strrchr(str, '\n') = '\0';
		err(F, Z, (char *[]){"{", str, "}", " Invalid vector format.\n", NULL});
		if (reserved)
			free(str);
		return (free_arr(arr), *error = true, (t_vec){0, 0, 0});
	}
	v.x = get_float(arr[0], error, 0);
	v.y = get_float(arr[1], error, 0);
	v.z = get_float(arr[2], error, 0);
	if (check_zero_vector(v, error) || *error)
		return (free_arr(arr), (t_vec){0, 0, 0});
	if (reserved)
		free(str);
	return (free_arr(arr), v);
}

t_color	get_color(char *str, bool *error, bool reserved)
{
	t_color		c;
	int			i;
	char		**arr;

	arr = ft_split(str, ',');
	i = 0;
	while (arr[i])
		i++;
	if (i != 3)
	{
		if (ft_strrchr(str, '\n'))
			*ft_strrchr(str, '\n') = '\0';
		err(F, Z, (char *[]){"{", str, "}", " Invalid color format.\n", NULL});
		if (reserved)
			free(str);
		return (free_arr(arr), *error = true, (t_color){0, 0, 0});
	}
	c.r = get_int(arr[0], error, 0) / 255.0;
	c.g = get_int(arr[1], error, 0) / 255.0;
	c.b = get_int(arr[2], error, 0) / 255.0;
	if (reserved)
		free(str);
	if (*error)
		return (free_arr(arr), (t_color){0, 0, 0});
	return (free_arr(arr), c);
}
