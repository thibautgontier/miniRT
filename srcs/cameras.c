/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cameras.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** Gets the camera information from the list, creates and fills
** an image with that information. Sends to the process functions.
*/

void			create_cameras(t_minirt *rt)
{
	t_list		*tmp;
	int			count;

	count = 1;
	tmp = rt->cam_list;
	while (tmp)
	{
		rt->camera = tmp->content;
		if (!(rt->camera->img.ptr = mlx_new_image(rt->mlx_ptr, \
	rt->resolution.x, rt->resolution.y)))
			error("fail to create Minilibx image", rt);
		if (!(rt->camera->img.add = mlx_get_data_addr(rt->camera->img.ptr, \
	&rt->camera->img.bpp, &rt->camera->img.size_line, &rt->camera->img.endian)))
			error("fail to get Minilibx image data", rt);
		setup_rt(rt);
		handle_threads(rt);
		if (rt->save)
			return ;
		count++;
		tmp = tmp->next;
	}
}

/*
** Moves down the list of cameras until it reaches the current one,
** fills the rt->camera with the corresponding value.
*/

void			choose_camera(t_minirt *rt)
{
	t_list		*tmp;
	int			count;

	count = 0;
	tmp = rt->cam_list;
	while (tmp)
	{
		if (rt->cur_cam == count)
		{
			rt->camera = tmp->content;
			rt->cur_cam++;
			if (rt->cur_cam == rt->cam_count)
				rt->cur_cam = 0;
			return ;
		}
		count++;
		tmp = tmp->next;
	}
}

void			change_camera(t_minirt *rt)
{
	if (rt->cam_count > 1)
	{
		choose_camera(rt);
		mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->camera->img.ptr,
								0, 0);
	}
}
