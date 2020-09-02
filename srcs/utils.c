/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_camera_and_texture(t_minirt *rt)
{
	t_list		*tmp;
	t_camera	*cam;
	t_element	*obj;

	tmp = rt->cam_list;
	while (tmp)
	{
		cam = tmp->content;
		if (cam->img.ptr)
			mlx_destroy_image(rt->mlx_ptr, cam->img.ptr);
		tmp = tmp->next;
	}
	tmp = rt->objs_list;
	while (tmp)
	{
		obj = tmp->content;
		tmp = tmp->next;
	}
}

/*
** Handles errors, writes the corresponding error
** message on the screen.
*/

void	error(char *str, t_minirt *rt)
{
	ft_putendl(str);
	if (rt->split)
		free_split(rt->split);
	if (rt->line)
		ft_strdel(&rt->line);
	free_camera_and_texture(rt);
	ft_lstclear(&rt->objs_list, free);
	ft_lstclear(&rt->cam_list, free);
	ft_lstclear(&rt->light_list, free);
	exit(EXIT_FAILURE);
}

/*
** Clears everything and exits.
*/

int		full_exit(t_minirt *rt)
{
	free_camera_and_texture(rt);
	ft_lstclear(&rt->objs_list, free);
	ft_lstclear(&rt->cam_list, free);
	ft_lstclear(&rt->light_list, free);
	if (!rt->save)
	{
		mlx_clear_window(rt->mlx_ptr, rt->win_ptr);
		mlx_destroy_window(rt->mlx_ptr, rt->win_ptr);
	}
	exit(EXIT_SUCCESS);
	return (1);
}

char	**free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		ft_strdel(&split[i]);
		i++;
	}
	free(split);
	split = NULL;
	return (split);
}

/*
** Handles basic keys, sends to functions for others.
*/

int		get_keypress(int key, t_minirt *rt)
{
	if (key == KEY_TAB)
		change_camera(rt);
	else if (key == KEY_ESC)
		full_exit(rt);
	if (key == KEY_V)
	{
		if (!rt->kb)
			rt->kb = 1;
		else
			rt->kb = 0;
		show_controls(rt);
	}
	handle_key(key, rt);
	return (1);
}
