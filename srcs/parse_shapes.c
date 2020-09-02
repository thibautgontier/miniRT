/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** For these functions, checks that the info is correct,
** mallocs for the size, and sends to get_vector. Gets the color
** and initializes the elements to the correct values.
*/

void	parse_sphere(t_minirt *rt)
{
	t_element	*sphere;
	int			split;

	split = count_split(rt->split);
	if (!(sphere = ft_calloc(1, sizeof(t_element))))
		error("Unable to malloc", rt);
	if (split < 4 || split > 6 || !check_split(rt->split, 5))
	{
		free(sphere);
		error("Could not parse sphere", rt);
	}
	sphere->id = 1;
	sphere->point = split_vector(rt->split[1], rt, 0);
	sphere->diameter = ft_atof(rt->split[2]);
	sphere->color = split_rgb(rt->split[3], rt);
	split >= 5 ? sphere->ref = ft_atof(rt->split[4]) : 0;
	ft_lstadd_back(&rt->objs_list, ft_lstnew(sphere));
	sphere->diameter < 0 ? error("Could not parse sphere", rt) : 0;
}

void	parse_plane(t_minirt *rt)
{
	t_element	*plane;
	int			split;

	split = count_split(rt->split);
	if (!(plane = ft_calloc(1, sizeof(t_element))))
		error("Unable to malloc", rt);
	if (split < 4 || split > 6 || !check_split(rt->split, 5))
	{
		free(plane);
		error("Could not parse plane", rt);
	}
	plane->id = 2;
	plane->point = split_vector(rt->split[1], rt, 0);
	plane->orientation = split_vector(rt->split[2], rt, 1);
	plane->color = split_rgb(rt->split[3], rt);
	split >= 5 ? plane->ref = ft_atof(rt->split[4]) : 0;
	ft_lstadd_back(&rt->objs_list, ft_lstnew(plane));
}

void	parse_square(t_minirt *rt)
{
	t_element	*square;
	int			split;

	split = count_split(rt->split);
	if (!(square = ft_calloc(1, sizeof(t_element))))
		error("Unable to malloc", rt);
	if (split < 5 || split > 7 || !check_split(rt->split, 6))
	{
		free(square);
		error("Could not parse square", rt);
	}
	square->id = 3;
	square->point = split_vector(rt->split[1], rt, 0);
	square->orientation = split_vector(rt->split[2], rt, 1);
	square->height = ft_atof(rt->split[3]);
	square->color = split_rgb(rt->split[4], rt);
	split >= 6 ? square->ref = ft_atof(rt->split[5]) : 0;
	ft_lstadd_back(&rt->objs_list, ft_lstnew(square));
	if (square->height < 0)
		error("Could not parse square", rt);
}

void	parse_cylinder(t_minirt *rt)
{
	t_element	*cylinder;
	int			split;

	split = count_split(rt->split);
	if (!(cylinder = ft_calloc(1, sizeof(t_element))))
		error("Unable to malloc", rt);
	if (split < 6 || split > 8 || !check_split(rt->split, 7))
	{
		free(cylinder);
		error("Could not parse cylinder.", rt);
	}
	cylinder->id = 4;
	cylinder->point = split_vector(rt->split[1], rt, 0);
	cylinder->orientation = normalize_vector(split_vector(rt->split[2], rt, 1));
	cylinder->diameter = ft_atof(rt->split[3]);
	cylinder->height = ft_atof(rt->split[4]);
	cylinder->color = split_rgb(rt->split[5], rt);
	split >= 7 ? cylinder->ref = ft_atof(rt->split[6]) : 0;
	ft_lstadd_back(&rt->objs_list, ft_lstnew(cylinder));
	if (cylinder->height < 0 || cylinder->diameter < 0)
		error("Could not parse cylinder", rt);
	create_circle(rt, cylinder, cylinder->height / 2 - 0.1, 1);
}

void	parse_triangle(t_minirt *rt)
{
	t_element	*triangle;
	int			split;

	split = count_split(rt->split);
	if (!(triangle = ft_calloc(1, sizeof(t_element))))
		error("Unable to malloc", rt);
	if (split < 5 || split > 7 || !check_split(rt->split, 6))
	{
		free(triangle);
		error("Could not parse triangle", rt);
	}
	triangle->id = 5;
	triangle->point = split_vector(rt->split[1], rt, 0);
	triangle->point2 = split_vector(rt->split[2], rt, 0);
	triangle->point3 = split_vector(rt->split[3], rt, 0);
	triangle->color = split_rgb(rt->split[4], rt);
	triangle->orientation = normalize_vector(cross_vector(\
		subtract_vectors(triangle->point2,
		triangle->point), subtract_vectors(triangle->point3, triangle->point)));
	split >= 6 ? triangle->ref = ft_atof(rt->split[5]) : 0;
	ft_lstadd_back(&rt->objs_list, ft_lstnew(triangle));
}
