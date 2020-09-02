/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void				fill_it(char **data, t_minirt *rt)
{
	int i;
	int j;
	int x;
	int y;

	i = 122;
	y = rt->resolution.y;
	while (y--)
	{
		x = -1;
		while (++x < rt->resolution.x)
		{
			j = (x * (rt->camera->img.bpp / 8)) + \
				(y * rt->camera->img.size_line);
			*(*data + i++) = *(rt->camera->img.add + j++);
			*(*data + i++) = *(rt->camera->img.add + j++);
			*(*data + i++) = *(rt->camera->img.add + j);
		}
	}
}

void				bmp_header(char **data, t_minirt *rt)
{
	unsigned int size;

	size = rt->resolution.y * rt->resolution.x * 3;
	*(unsigned short *)*data = *(const unsigned int *)(unsigned long)"BM";
	*(unsigned int *)(*data + 2) = (size + 122);
	*(unsigned int *)(*data + 6) = 0u;
	*(unsigned char *)(*data + 10) = 122;
	*(unsigned int *)(*data + 14) = 122 - 14;
	*(unsigned int *)(*data + 18) = rt->resolution.x;
	*(unsigned int *)(*data + 22) = rt->resolution.y;
	*(unsigned short *)(*data + 26) = 1;
	*(unsigned short *)(*data + 28) = 24;
	*(unsigned int *)(*data + 30) = 0;
	*(unsigned int *)(*data + 34) = (unsigned int)size;
	*(unsigned int *)(*data + 38) = 3780;
	*(unsigned int *)(*data + 42) = 3780;
	*(int *)(*data + 46) = 0;
	*(int *)(*data + 50) = 0;
}

/*
** Creates a new file for the image, calculate padding, then sends
** to helper functions to create the headers. Then writes in the data.
*/

void				create_bmp_image(t_minirt *rt, char *name)
{
	int				fd;
	unsigned int	size;
	unsigned int	i;
	char			*data;

	size = rt->resolution.y * rt->resolution.x * 3;
	if (!(data = malloc((size + 122))))
		error("could not malloc data", rt);
	i = 0;
	while (i < size + 122)
		data[i++] = 0;
	bmp_header(&data, rt);
	fill_it(&data, rt);
	if ((fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 0644)) <= 0)
		error("could not open file", rt);
	write(fd, data, (size + 122));
	close(fd);
}
