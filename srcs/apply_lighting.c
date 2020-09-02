/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color			apply_intensity(float intensity, t_color color)
{
	if (intensity > 1)
		return (color);
	color.r = color.r * intensity;
	color.g = color.g * intensity;
	color.b = color.b * intensity;
	return (color);
}

t_vector		vector_light(t_element *light, t_vector p)
{
	t_vector	vector;

	vector.x = 0;
	vector.y = 0;
	vector.z = 0;
	if (light->id == DIFFUSE)
	{
		vector = normalize_vector(subtract_vectors(light->point, p));
		light->orientation = vector;
	}
	else if (light->id == DIRECTIONAL)
		vector = light->orientation;
	return (vector);
}

/*
** Check if light is diffused, orients the camera plane to point
** in the right direction.
*/

static	int		get_side_of_plane(t_minirt *rt, t_element *light, t_vector ori,
					t_vector direct)
{
	t_element	plane_camera;
	t_element	light_2;
	t_minirt	rt_2;

	if (rt->obj->id != PLANE && rt->obj->id != CIRCLE && rt->obj->id != SQUARE
		&& rt->obj->id != TRIANGLE)
		return (1);
	rt_2.t = INT_MAX;
	if (light->id == DIFFUSE)
	{
		light_2.orientation = direct;
		light_2.point = light->point;
		solve_plane(&rt_2, &light_2, ori, direct);
	}
	rt_2.k = rt_2.t;
	plane_camera.point = rt->ray.orientation;
	plane_camera.orientation = direct;
	rt_2.t = INT_MAX;
	solve_plane(&rt_2, &plane_camera, ori, direct);
	if (rt_2.t == INT_MAX && rt_2.k == INT_MAX)
		return (-1);
	if (rt_2.t != INT_MAX && rt_2.k != INT_MAX)
		return (1);
	return (0);
}

/*
** This function applies the different brightnesses of
** each color to give the image a depth and perspective.
*/

t_color			color_shade(t_minirt *rt, t_vector p, \
	t_vector n, t_color color)
{
	t_list		*lst;
	float		point;
	t_element	*light;
	t_vector	vector;

	lst = rt->light_list;
	while (lst)
	{
		light = element_cpy(lst->content, rt);
		vector = vector_light(light, p);
		point = get_point(n, vector);
		point *= get_side_of_plane(rt, light, rt->obj->point, n);
		if (point <= 0 || apply_shadows(rt, p, vector, light))
		{
			lst = lst->next;
			free(light);
			continue;
		}
		color = add_color(color, get_color_average(rt->color,
			apply_intensity(light->ratio * point, light->color)), 1);
		free(light);
		lst = lst->next;
	}
	return (color);
}

t_color			apply_lights(t_minirt *rt)
{
	t_vector	n;
	t_color		color;

	color = get_color_average(rt->color,
		apply_intensity(rt->ambient.ratio, rt->ambient.color));
	n = get_normal_vector(rt, rt->vector);
	color = color_shade(rt, rt->vector, n, color);
	return (color);
}
