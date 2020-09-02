/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		count_objects(t_list *lst)
{
	int			count;
	t_list		*tmp;
	t_element	*obj;

	tmp = lst;
	count = 0;
	while (tmp)
	{
		obj = tmp->content;
		tmp = tmp->next;
		if (!obj->nm)
			count++;
	}
	return (count);
}

void	move_color(t_minirt *rt, int reset)
{
	if (reset)
	{
		rt->move_obj->color.r = rt->tmp_color.r;
		rt->move_obj->color.g = rt->tmp_color.g;
		rt->move_obj->color.b = rt->tmp_color.b;
	}
	else
	{
		rt->tmp_color.r = rt->move_obj->color.r;
		rt->tmp_color.g = rt->move_obj->color.g;
		rt->tmp_color.b = rt->move_obj->color.b;
		rt->move_obj->color.r = fabs(rt->move_obj->color.r - 1);
		rt->move_obj->color.g = fabs(rt->move_obj->color.g - 1);
		rt->move_obj->color.b = fabs(rt->move_obj->color.b - 1);
	}
}

void	unselect_objects(t_minirt *rt)
{
	if (rt->move_obj)
		move_color(rt, 1);
	rt->cur_obj = 0;
	rt->move_obj = NULL;
}

void	select_objects(t_minirt *rt)
{
	t_list		*tmp;
	int			count;

	count = 0;
	tmp = rt->objs_list;
	while (tmp)
	{
		if (((t_element*)tmp->content)->nm && (tmp = tmp->next))
			continue ;
		if (rt->cur_obj == count)
		{
			if (rt->move_obj)
				move_color(rt, 1);
			rt->move_obj = tmp->content;
			rt->cur_obj++;
			move_color(rt, 0);
			if (rt->cur_obj == rt->obj_count)
				rt->cur_obj = 0;
			return ;
		}
		count++;
		tmp = tmp->next;
	}
}
