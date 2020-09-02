/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient(t_minirt *rt)
{
	if (count_split(rt->split) != 3 || !check_split(rt->split, 0))
		error("Ambient light parsing failed.", rt);
	rt->ambient.ratio = ft_atof(rt->split[1]);
	rt->ambient.color = split_rgb(rt->split[2], rt);
	if (rt->ambient.ratio > 1 || rt->ambient.ratio < 0)
		error("Ambient light parsing failed.", rt);
	rt->ambient.parsed = 1;
}

void	parse_resolution(t_minirt *rt)
{
	if (count_split(rt->split) != 3 || !check_split(rt->split, 0))
		error("invalid resolution", rt);
	rt->resolution.x = ft_atoi(rt->split[1]);
	rt->resolution.y = ft_atoi(rt->split[2]);
	if (rt->resolution.x < 1 || rt->resolution.y < 1)
		error("resolution too small", rt);
	rt->resolution.parsed = 1;
	rt->resolution.x > 1440 ? rt->resolution.x = 1440 : 0;
	rt->resolution.y > 850 ? rt->resolution.y = 850 : 0;
}

void	parse_camera(t_minirt *rt)
{
	t_camera		*camera;

	if (!(camera = ft_calloc(1, sizeof(t_camera))))
		error("fail to malloc", rt);
	if (count_split(rt->split) != 3 || !check_split(rt->split, 0))
	{
		free(camera);
		error("camera parsing error", rt);
	}
	camera->pov = split_vector(rt->split[1], rt, 0);
	camera->orientation = split_vector(rt->split[2], rt, 1);
	ft_lstadd_back(&rt->cam_list, ft_lstnew(camera));
}

void	parse_light(t_minirt *rt)
{
	t_element		*light;

	if (!(light = ft_calloc(1, sizeof(t_element))))
		error("fail to malloc", rt);
	if (count_split(rt->split) != 4 || !check_split(rt->split, 0))
	{
		free(light);
		error("light parsing error", rt);
	}
	light->id = 10;
	light->point = split_vector(rt->split[1], rt, 0);
	light->ratio = ft_atof(rt->split[2]);
	light->color = split_rgb(rt->split[3], rt);
	ft_lstadd_back(&rt->light_list, ft_lstnew(light));
	if (light->ratio > 1 || light->ratio < 0)
		error("light parsing error", rt);
}

/*
** Opens the file, reads it line by line. For each line,
** splits it looking for whitespaces. Sends to check_id to
** find out which line it is. Makes sure that all the info is there.
*/

void	parse_file(char *rt_file, t_minirt *rt)
{
	int		fd;

	if ((fd = open(rt_file, O_RDONLY)) < 0)
		error("fail to open scene file", rt);
	while (get_next_line(fd, &rt->line) > 0)
	{
		rt->split = ft_ssplit(rt->line, " \t\v\n\r\f");
		if (rt->split[0])
			check_id(rt);
		rt->split = free_split(rt->split);
		ft_strdel(&rt->line);
	}
	close(fd);
	rt->obj_count = count_objects(rt->objs_list);
	if (!(rt->cam_count = ft_lstsize(rt->cam_list)))
		error("no camera available", rt);
	if (!rt->resolution.parsed)
		error("no resolution", rt);
}
