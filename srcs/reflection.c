/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector		get_normal_vector_cylinder(t_element *cylinder, t_vector p)
{
	t_element	plan;
	t_minirt	rtt;

	plan.orientation = cylinder->orientation;
	plan.point = cylinder->point;
	rtt.t = INT_MAX;
	solve_plane(&rtt, &plan, p, cylinder->orientation);
	if (rtt.t != INT_MAX)
	{
		return (normalize_vector(subtract_vectors(p, \
	add_vectors(cylinder->point, \
	multiply_vectors(cylinder->orientation, rtt.t * -1)))));
	}
	solve_plane(&rtt, &plan, p, multiply_vectors(cylinder->orientation, -1));
	return (normalize_vector(subtract_vectors(p, add_vectors(cylinder->point,
		multiply_vectors(cylinder->orientation, rtt.t)))));
}

t_vector		get_normal_vector(t_minirt *rt, t_vector p)
{
	t_vector	norm_vec;

	if (rt->obj->id == PLANE || rt->obj->id == CIRCLE || rt->obj->id == SQUARE
		|| rt->obj->id == TRIANGLE)
		norm_vec = normalize_vector(rt->obj->orientation);
	else if (rt->obj->id == CYLINDER)
		norm_vec = get_normal_vector_cylinder(rt->obj, p);
	else
		norm_vec = normalize_vector(subtract_vectors(p, rt->obj->point));
	return (norm_vec);
}

t_color			color_average_intensity(t_color color1, \
	t_color color2, float intens)
{
	t_color		color;

	if (intens == 0)
		return (color1);
	color.r = (color1.r + color2.r * intens) / 2;
	color.g = (color1.g + color2.g * intens) / 2;
	color.b = (color1.b + color2.b * intens) / 2;
	return (color);
}

void			reflect_2(t_minirt *rt, t_minirt rtt)
{
	rt->obj->ref < 0 ? rtt.ray.direction = normalize_vector(\
		subtract_vectors(rt->ray.direction,
		multiply_vectors(multiply_vectors(rtt.ray.direction, \
			get_point(multiply_vectors(rtt.ray.direction, rt->obj->ref),
		rt->ray.direction)), 2))) : rtt.ray.direction;
	rtt.ray.orientation = add_vectors(rtt.ray.orientation, \
	multiply_vectors(rtt.ray.direction, 0.2));
	rtt.color = ray_intersect(&rtt);
	rt->obj->ref > 0 ? rt->color = color_average_intensity(rt->color, rtt.color,
		rt->obj->ref) : rt->color;
	rt->obj->ref < 0 ? rt->color = color_average_intensity(rt->color, \
	rtt.color, 1) : rt->color;
}

void			reflect(t_minirt *rt)
{
	t_minirt	rtt;

	rt->nbref++;
	if (rt->nbref > MAX_REF)
		return ;
	ft_memcpy(&rtt, rt, sizeof(t_minirt));
	rtt.ray.orientation = rt->vector;
	rtt.ray.direction = get_normal_vector(rt, rtt.ray.orientation);
	rt->obj->ref < 0 ? rtt.ray.direction = \
		multiply_vectors(rtt.ray.direction, -1) : rtt.ray.direction;
	rt->obj->ref > 0 ? rtt.ray.direction = normalize_vector(subtract_vectors(\
		rt->ray.direction, multiply_vectors(multiply_vectors(\
		rtt.ray.direction, \
			get_point(rtt.ray.direction, rt->ray.direction)), 2)))
		: rtt.ray.direction;
	reflect_2(rt, rtt);
}
