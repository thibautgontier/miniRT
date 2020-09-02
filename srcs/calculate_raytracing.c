/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_raytracing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			find_objects(t_minirt *rt, t_element *obj, \
	t_vector ori, t_vector dir)
{
	if (obj->id == SPHERE)
		solve_sphere(rt, obj, ori, dir);
	else if (obj->id == PLANE)
		solve_plane(rt, obj, ori, dir);
	else if (obj->id == CYLINDER)
		solve_cylinder(rt, obj, ori, dir);
	else if (obj->id == CIRCLE)
		solve_circle(rt, obj, ori, dir);
	else if (obj->id == TRIANGLE)
		solve_triangle(rt, obj, ori, dir);
	else if (obj->id == SQUARE)
		solve_square(rt, obj, ori, dir);
}

t_color			ray_intersect(t_minirt *rt)
{
	t_list		*tmp;

	rt->obj = NULL;
	rt->t = INT_MAX;
	rt->k = INT_MAX;
	ft_bzero(&rt->color, sizeof(t_color));
	tmp = rt->objs_list;
	while (tmp)
	{
		find_objects(rt, tmp->content, rt->ray.orientation, rt->ray.direction);
		if (rt->t > 0 && rt->t < rt->k && (rt->k = rt->t))
			rt->obj = tmp->content;
		tmp = tmp->next;
	}
	if (rt->obj)
	{
		rt->vector = add_vectors(rt->ray.orientation, \
	multiply_vectors(rt->ray.direction, rt->k));
		rt->color = get_color(rt);
		rt->obj->ref ? reflect(rt) : 0;
		rt->color = apply_lights(rt);
	}
	return (rt->color);
}

t_vector		calculate_ray(t_minirt *rt, float x, float y)
{
	t_vector	dir;
	float		norm_x;
	float		norm_y;
	t_vector	image_point;

	norm_x = ((x / (float)rt->resolution.x) - 0.5);
	norm_y = ((y / (float)rt->resolution.y) - 0.5);
	rt->resolution.x < rt->resolution.y ? norm_x *= rt->aspect : 0;
	rt->resolution.x > rt->resolution.y ? norm_y /= rt->aspect : 0;
	image_point = add_vectors(add_vectors(add_vectors(\
	multiply_vectors(rt->camera->right, norm_x),
		multiply_vectors(rt->camera->up, norm_y)), rt->ray.orientation),
		normalize_vector(rt->camera->orientation));
	dir = normalize_vector(subtract_vectors(image_point, rt->ray.orientation));
	return (dir);
}

void			raytracing(t_thread *th)
{
	float		i;
	float		j;
	float		st;

	j = 0;
	st = 0;
	th->scene.st && th->current % 2 == 1 ? \
		st = round(th->scene.resolution.x / 50) : 0;
	while (j < th->scene.resolution.y && (i = th->current) >= 0)
	{
		while (i < th->scene.resolution.x && (th->scene.nbref = 0) == 0)
		{
			th->scene.ray.direction = calculate_ray(&th->scene, i - st, j);
			th->scene.color = ray_intersect(&th->scene);
			fill_color(&th->scene, i, j);
			i += THREADS;
		}
		th->scene.percent = (int)(j * 100 / th->scene.resolution.y) + 1;
		j++;
	}
	pthread_exit(NULL);
}
