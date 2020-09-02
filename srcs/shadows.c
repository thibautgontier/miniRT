/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		apply_shadows(t_minirt *rt, t_vector ori, \
	t_vector dir, t_element *light)
{
	t_list		*tmp;
	t_element	*obj;

	tmp = rt->objs_list;
	rt->t = INT_MAX;
	solve_plane(rt, light, ori, dir);
	rt->k = rt->t - 0.1;
	while (tmp)
	{
		obj = tmp->content;
		if (rt->obj == obj)
		{
			rt->obj->id == CYLINDER ? tmp = tmp->next->next : 0;
			tmp = tmp->next;
			continue ;
		}
		find_objects(rt, tmp->content, ori, dir);
		if (rt->t > 0 && rt->t < rt->k)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
