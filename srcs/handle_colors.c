/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		fill_color(t_minirt *rt, int x, int y)
{
	int		i;
	int		column;
	int		row;

	i = y * rt->camera->img.size_line + rt->camera->img.bpp / 8 * x;
	column = 0;
	row = 0;
	if (rt->st)
	{
		if (rt->tr % 2 == 0)
			rt->color.r = 0;
		else
			rt->color.g = 0;
	}
	if (i < 1)
		return ;
	rt->camera->img.add[i] = rt->color.b * 255;
	rt->camera->img.add[i + 1] = rt->color.g * 255;
	rt->camera->img.add[i + 2] = rt->color.r * 255;
}

t_color		get_color_average(t_color color1, t_color color2)
{
	t_color		color;

	color.r = color1.r * color2.r;
	color.g = color1.g * color2.g;
	color.b = color1.b * color2.b;
	return (color);
}

t_color		add_color(t_color color1, t_color color2, int cap)
{
	t_color		color;

	color.r = color1.r + color2.r;
	color.r > 1 && cap ? color.r = 1 : 0;
	color.g = color1.g + color2.g;
	color.g > 1 && cap ? color.g = 1 : 0;
	color.b = color1.b + color2.b;
	color.b > 1 && cap ? color.b = 1 : 0;
	return (color);
}

t_color		divide_color(t_color color, int average)
{
	t_color		c;

	c.r = color.r / average;
	c.g = color.g / average;
	c.b = color.b / average;
	return (c);
}

t_color		get_color(t_minirt *rt)
{
	t_color	color;

	color = rt->obj->color;
	return (color);
}
