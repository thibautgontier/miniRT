/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_objects_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void				solve_sphere(t_minirt *rt, t_element *sphere, \
	t_vector ori, t_vector dir)
{
	t_solve			s;

	s.sub = subtract_vectors(ori, sphere->point);
	s.a = get_point(dir, dir);
	s.b = 2 * get_point(dir, s.sub);
	s.c = get_point(s.sub, s.sub) - pow(sphere->diameter / 2, 2);
	s.det = pow(s.b, 2) - (4 * s.a * s.c);
	if (s.det < 0)
		return ;
	s.det = sqrt(s.det);
	s.a = 2 * s.a;
	s.t1 = (-s.b - s.det) / s.a;
	s.t2 = (-s.b + s.det) / s.a;
	if (s.t1 >= 0 && rt->t > s.t1)
		rt->t = s.t1;
	else if (s.t2 >= 0 && rt->t > s.t2)
		rt->t = s.t2;
}

void				create_square(t_minirt *rt, t_element *cube, \
	t_vector point, t_vector orient)
{
	t_element		*square;

	if (!(square = ft_calloc(1, sizeof(t_element))))
		error("fail to malloc", rt);
	square->id = 3;
	square->nm = 1;
	square->point = point;
	square->orientation = orient;
	square->height = cube->height;
	square->color = cube->color;
	ft_lstadd_back(&rt->objs_list, ft_lstnew(square));
}

void				solve_square(t_minirt *rt, t_element *square, \
	t_vector ori, t_vector dir)
{
	t_solve			s;
	t_vector		d;

	s.a = get_point(subtract_vectors(ori, square->point), square->orientation);
	s.b = get_point(dir, square->orientation);
	if (s.b == 0 || (s.a < 0 && s.b < 0) || (s.a > 0 && s.b > 0))
		return ;
	s.t1 = -s.a / s.b;
	d = subtract_vectors(add_vectors(multiply_vectors(dir, s.t1), ori), \
		square->point);
	s.t2 = square->height / 2;
	if (fabs(d.x) > s.t2 || fabs(d.y) > s.t2 || fabs(d.z) > s.t2)
		return ;
	if (s.t1 > 0)
		rt->t = s.t1;
}

void				solve_triangle(t_minirt *rt, \
	t_element *triangle, t_vector ori, t_vector dir)
{
	t_solve			s;
	t_vector		v1;
	t_vector		v2;
	t_vector		tvec;
	t_vector		pvec;

	v1 = subtract_vectors(triangle->point2, triangle->point);
	v2 = subtract_vectors(triangle->point3, triangle->point);
	pvec = cross_vector(dir, v2);
	s.det = get_point(v1, pvec);
	if (fabs(s.det) < 0.00001)
		return ;
	s.c = 1 / s.det;
	tvec = subtract_vectors(ori, triangle->point);
	s.a = get_point(tvec, pvec) * s.c;
	if (s.a < 0 || s.a > 1)
		return ;
	tvec = cross_vector(tvec, v1);
	s.b = get_point(dir, tvec) * s.c;
	if (s.b < 0 || s.a + s.b > 1)
		return ;
	rt->t = get_point(v2, tvec) * s.c;
}
