/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			check_id(t_minirt *rt)
{
	if (ft_strequ(rt->split[0], "R") && !rt->resolution.parsed)
		parse_resolution(rt);
	else if (ft_strequ(rt->split[0], "A") && !rt->ambient.parsed)
		parse_ambient(rt);
	else if (ft_strequ(rt->split[0], "c"))
		parse_camera(rt);
	else if (ft_strequ(rt->split[0], "l"))
		parse_light(rt);
	else if (ft_strequ(rt->split[0], "sp"))
		parse_sphere(rt);
	else if (ft_strequ(rt->split[0], "pl"))
		parse_plane(rt);
	else if (ft_strequ(rt->split[0], "sq"))
		parse_square(rt);
	else if (ft_strequ(rt->split[0], "cy"))
		parse_cylinder(rt);
	else if (ft_strequ(rt->split[0], "tr"))
		parse_triangle(rt);
	else if (rt->split[0][0] == '#' || ft_strequ(rt->split[0], "#"))
		;
	else
		error("parsing error", rt);
}

int				check_split(char **split, int max)
{
	int			i;
	int			j;

	i = 1;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (!ft_isdigit(split[i][j]) && split[i][j] != ',' &&
				split[i][j] != '.' && split[i][j] != '-' && (!max || i < max))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_vector		split_vector(char *str, t_minirt *rt, int orient)
{
	t_vector	v;
	char		**split;

	split = ft_split(str, ',');
	if (count_split(split) != 3 || ft_str_c_count(str, ',') != 2
		|| !check_split(split, 0))
	{
		free_split(split);
		error("invalid vector parsing", rt);
	}
	v.x = ft_atof(split[0]);
	v.y = ft_atof(split[1]);
	v.z = ft_atof(split[2]);
	free_split(split);
	if (orient && ((v.x > 1 || v.y > 1 || v.z > 1 || v.x < -1 || v.y < -1
		|| v.z < -1)))
		error("invalid vector parsing", rt);
	return (v);
}

t_color			split_rgb(char *str, t_minirt *rt)
{
	t_color		c;
	char		**split;

	split = ft_split(str, ',');
	if (count_split(split) != 3 || ft_str_c_count(str, ',') != 2
		|| !check_split(split, 0))
	{
		free_split(split);
		error("invalid rgb parsing", rt);
	}
	c.r = ft_atof(split[0]) / 255;
	c.g = ft_atof(split[1]) / 255;
	c.b = ft_atof(split[2]) / 255;
	free_split(split);
	if (c.r > 1 || c.g > 1 || c.b > 1 || c.r < 0 || c.g < 0 || c.b < 0)
		error("invalid rgb parsing", rt);
	return (c);
}
