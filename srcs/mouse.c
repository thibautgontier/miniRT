/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		mouse_click(int button, int x, int y, t_minirt *rt)
{
	(void)x;
	(void)y;
	if (button == 1)
		rt->mouse = 1;
	return (1);
}

int		mouse_unclick(int button, int x, int y, t_minirt *rt)
{
	(void)x;
	(void)y;
	if (button == 1)
		rt->mouse = 0;
	return (1);
}

int		mouse_position(int x, int y, t_minirt *rt)
{
	if (x > 0 && x <= rt->resolution.x && y > 0 && \
	y < rt->resolution.y && rt->mouse)
	{
		if (x < rt->resolution.x / 3)
			rt->camera->orientation.x -= 0.1;
		else if (x > rt->resolution.x - rt->resolution.x / 3)
			rt->camera->orientation.x += 0.1;
		else if (y < rt->resolution.y / 3)
			rt->camera->orientation.y += 0.1;
		else if (y > rt->resolution.y - rt->resolution.y / 3)
			rt->camera->orientation.y -= 0.1;
		check_orientation(&rt->camera->orientation);
		redraw_window(rt);
	}
	return (1);
}
