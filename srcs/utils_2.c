/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** Makes sure that the values are within the acceptable range,
** corrects them if not.
*/

int			check_orientation(t_vector *vector)
{
	if (vector->x > 1)
		vector->x = 1;
	else if (vector->x < -1)
		vector->x = -1;
	if (vector->y > 1)
		vector->y = 1;
	else if (vector->y < -1)
		vector->y = -1;
	if (vector->z > 1)
		vector->z = 1;
	else if (vector->z < -1)
		vector->z = -1;
	else
		return (1);
	return (0);
}

int			count_split(char **split)
{
	int		count;

	count = 0;
	while (split[count])
		count++;
	return (count);
}

void		show_controls(t_minirt *rt)
{
	if (rt->kb)
	{
		mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 5, 0xFFFF00,
			"-------------------------------------------");
		mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 175, 0xFFFF00,
			"-------------------------------------------");
		mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 110, 0xFFFF00,
			"Switch Camera : TAB                        |");
		mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 90, 0xFFFF00,
			"Move Camera : W,A,S,D,Q,E                  |");
		mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 70, 0xFFFF00,
			"Orient Camera : T,F,G,H,R,Y                |");
		mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 50, 0xFFFF00,
			"Select Object : ENTER                      |");
		mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 30, 0xFFFF00,
			"Unselect Object : \\                        |");
		mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 150, 0xFFFF00,
			"Move Object : UP,LEFT,DOWN,RIGHT,N,M       |");
		mlx_string_put(rt->mlx_ptr, rt->win_ptr, 10, 130, 0xFFFF00,
			"Orient Object : I,J,K,L,U,O                |");
	}
	else
		mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->camera->img.ptr,
			0, 0);
}

/*
** Draws a new iteration of the window, brand new.
*/

void		redraw_window(t_minirt *rt)
{
	setup_rt(rt);
	handle_threads(rt);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, \
		rt->camera->img.ptr, 0, 0);
	show_controls(rt);
}

/*
** Allocates and copies a new element.
*/

t_element	*element_cpy(t_element *elem, t_minirt *rt)
{
	t_element	*new;

	if (!(new = calloc(1, sizeof(t_element))))
		error("Failed to allocate memory.", rt);
	ft_memcpy(new, elem, sizeof(t_element));
	return (new);
}
