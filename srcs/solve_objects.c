/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			create_circle(t_minirt *rt, t_element *cylinder, \
	float t, int create)
{
	t_element	*circle;

	if (!(circle = ft_calloc(1, sizeof(t_element))))
		error("fail to malloc", rt);
	circle->id = 6;
	circle->nm = 1;
	circle->point = add_vectors(cylinder->point,
		multiply_vectors(normalize_vector(cylinder->orientation), t));
	circle->orientation = cylinder->orientation;
	circle->diameter = cylinder->diameter;
	circle->color = cylinder->color;
	circle->ref = cylinder->ref;
	ft_lstadd_back(&rt->objs_list, ft_lstnew(circle));
	if (create)
		create_circle(rt, cylinder, (cylinder->height / -2) + 0.1, 0);
}

void			solve_circle(t_minirt *rt, t_element *circle, \
	t_vector ori, t_vector dir)
{
	t_solve		solver;
	t_vector	inter;

	solver.a = get_point(subtract_vectors(ori, \
		circle->point), circle->orientation);
	solver.b = get_point(dir, circle->orientation);
	if (solver.b == 0 || (solver.a < 0 && solver.b < 0) || \
		(solver.a > 0 && solver.b > 0))
		return ;
	solver.t1 = -solver.a / solver.b;
	if (solver.t1 < 0 || rt->t < solver.t1)
		return ;
	inter = add_vectors(ori, multiply_vectors(dir, solver.t1));
	inter = subtract_vectors(inter, circle->point);
	solver.det = sqrt(get_point(inter, inter));
	solver.det <= circle->diameter / 2 ? rt->t = solver.t1 : 0;
}

static	void	inter(t_minirt *rt, t_element *cylinder, t_solve solver,
					t_minirt test)
{
	t_element	plane;
	t_vector	inter;
	float		t;

	t = INT_MAX;
	if (solver.t1 >= 0 && rt->t > solver.t1)
		t = solver.t1;
	else if (solver.t2 >= 0 && rt->t > solver.t2)
		t = solver.t2;
	if (t == INT_MAX)
		return ;
	inter = add_vectors(test.ray.orientation, \
		multiply_vectors(test.ray.direction, t));
	plane.orientation = cylinder->orientation;
	plane.point = cylinder->point;
	test.t = INT_MAX;
	solve_plane(&test, &plane, inter, cylinder->orientation);
	test.t <= cylinder->height / 2 ? rt->t = t : 0;
	solve_plane(&test, &plane, inter, \
		multiply_vectors(cylinder->orientation, -1));
	test.t <= cylinder->height / 2 ? rt->t = t : 0;
}

void			solve_cylinder(t_minirt *rt, t_element *cylinder, \
	t_vector orientation, t_vector dir)
{
	t_solve		solver;
	t_minirt	test;
	t_vector	vec;

	test.ray.orientation = orientation;
	test.ray.direction = dir;
	solver.cross = cross_vector(test.ray.direction, cylinder->orientation);
	solver.sub = subtract_vectors(test.ray.orientation, cylinder->point);
	vec = cross_vector(solver.sub, cylinder->orientation);
	solver.a = get_point(solver.cross, solver.cross);
	solver.b = 2 * get_point(solver.cross, vec);
	solver.c = get_point(vec, vec) - \
		(pow(cylinder->diameter / 2, 2) \
	* get_point(cylinder->orientation, cylinder->orientation));
	solver.det = pow(solver.b, 2) - (4 * solver.a * solver.c);
	if (solver.det < 0)
		return ;
	solver.a = 2 * solver.a;
	solver.det = sqrt(solver.det);
	solver.t1 = (-solver.b - solver.det) / solver.a;
	solver.t2 = (-solver.b + solver.det) / solver.a;
	inter(rt, cylinder, solver, test);
}

void			solve_plane(t_minirt *rt, t_element *plane, \
	t_vector ori, t_vector dir)
{
	t_solve		s;

	s.a = get_point(subtract_vectors(ori, plane->point), plane->orientation);
	s.b = get_point(dir, plane->orientation);
	if (s.b == 0 || (s.a < 0 && s.b < 0) || (s.a > 0 && s.b > 0))
		return ;
	s.t1 = -s.a / s.b;
	if (s.t1 < 0 || rt->t < s.t1)
		return ;
	rt->t = s.t1;
}
