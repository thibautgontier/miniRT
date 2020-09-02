/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** All these functions check which key gets pressed and
** initializes the struct elements accordingly.
*/

int		handle_key5(int key, t_minirt *rt)
{
	if (key == KEY_DOWN && rt->move_obj && rt->move_obj->id == TRIANGLE)
	{
		rt->move_obj->point.y--;
		rt->move_obj->point2.y--;
		rt->move_obj->point3.y--;
	}
	else if (key == KEY_LEFT && rt->move_obj && rt->move_obj->id == TRIANGLE)
	{
		rt->move_obj->point.x--;
		rt->move_obj->point2.x--;
		rt->move_obj->point3.x--;
	}
	else if (key == KEY_RIGHT && rt->move_obj && rt->move_obj->id == TRIANGLE)
	{
		rt->move_obj->point.x++;
		rt->move_obj->point2.x++;
		rt->move_obj->point3.x++;
	}
	else
		return (0);
	return (1);
}

int		handle_key4(int key, t_minirt *rt)
{
	if (key == KEY_N && rt->move_obj && rt->move_obj->id == TRIANGLE)
	{
		rt->move_obj->point.z--;
		rt->move_obj->point2.z--;
		rt->move_obj->point3.z--;
	}
	else if (key == KEY_M && rt->move_obj && rt->move_obj->id == TRIANGLE)
	{
		rt->move_obj->point.z++;
		rt->move_obj->point2.z++;
		rt->move_obj->point3.z++;
	}
	else if (key == KEY_UP && rt->move_obj && rt->move_obj->id == TRIANGLE)
	{
		rt->move_obj->point.y++;
		rt->move_obj->point2.y++;
		rt->move_obj->point3.y++;
	}
	else if (handle_key5(key, rt))
		return (1);
	else
		return (0);
	return (1);
}

int		handle_key3(int key, t_minirt *rt)
{
	if (key == KEY_I && rt->move_obj)
		rt->move_obj->orientation.y += 0.1;
	else if (key == KEY_K && rt->move_obj)
		rt->move_obj->orientation.y -= 0.1;
	else if (key == KEY_J && rt->move_obj)
		rt->move_obj->orientation.x -= 0.1;
	else if (key == KEY_L && rt->move_obj)
		rt->move_obj->orientation.x += 0.1;
	else if (key == KEY_U && rt->move_obj)
		rt->move_obj->orientation.z -= 0.1;
	else if (key == KEY_O && rt->move_obj)
		rt->move_obj->orientation.z += 0.1;
	else if (key == KEY_N && rt->move_obj && rt->move_obj->id != TRIANGLE)
		rt->move_obj->point.z--;
	else if (key == KEY_M && rt->move_obj && rt->move_obj->id != TRIANGLE)
		rt->move_obj->point.z++;
	else if (key == KEY_G)
		rt->camera->orientation.y -= 0.1;
	else
		return (0);
	if (rt->move_obj)
		check_orientation(&rt->move_obj->orientation);
	return (1);
}

int		handle_key2(int key, t_minirt *rt)
{
	if (key == KEY_T)
		rt->camera->orientation.y += 0.1;
	else if (key == KEY_R)
		rt->camera->orientation.z -= 0.1;
	else if (key == KEY_Y)
		rt->camera->orientation.z += 0.1;
	else if (key == KEY_ENTER)
		select_objects(rt);
	else if (key == KEY_PIPE)
		unselect_objects(rt);
	else if (key == KEY_UP && rt->move_obj && rt->move_obj->id != TRIANGLE)
		rt->move_obj->point.y++;
	else if (key == KEY_DOWN && rt->move_obj && rt->move_obj->id != TRIANGLE)
		rt->move_obj->point.y--;
	else if (key == KEY_LEFT && rt->move_obj && rt->move_obj->id != TRIANGLE)
		rt->move_obj->point.x--;
	else if (key == KEY_RIGHT && rt->move_obj && rt->move_obj->id != TRIANGLE)
		rt->move_obj->point.x++;
	else if (handle_key3(key, rt))
		return (1);
	else if (handle_key4(key, rt))
		return (1);
	else
		return (0);
	return (1);
}

int		handle_key(int key, t_minirt *rt)
{
	if (key == KEY_W)
		rt->camera->pov.y++;
	else if (key == KEY_S)
		rt->camera->pov.y--;
	else if (key == KEY_A)
		rt->camera->pov.x--;
	else if (key == KEY_D)
		rt->camera->pov.x++;
	else if (key == KEY_Q)
		rt->camera->pov.z--;
	else if (key == KEY_E)
		rt->camera->pov.z++;
	else if (key == KEY_F)
		rt->camera->orientation.x -= 0.1;
	else if (key == KEY_H)
		rt->camera->orientation.x += 0.1;
	else if (handle_key2(key, rt))
		;
	else
		return (0);
	if (!check_orientation(&rt->camera->orientation))
		return (0);
	redraw_window(rt);
	return (1);
}
