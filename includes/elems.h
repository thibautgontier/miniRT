/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elems.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMS_H
# define ELEMS_H

typedef struct	s_rez
{
	int			x;
	int			y;
	int			parsed;
}				t_rez;

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef struct	s_color
{
	float		r;
	float		g;
	float		b;
}				t_color;

typedef struct	s_ray
{
	t_vector	orientation;
	t_vector	direction;
}				t_ray;

typedef struct	s_solve
{
	float		a;
	float		b;
	float		c;
	float		det;
	float		t1;
	float		t2;
	float		d1;
	float		d2;
	t_vector	sub;
	t_vector	cross;
}				t_solve;

typedef struct	s_ambient
{
	float		ratio;
	int			parsed;
	t_color		color;
}				t_ambient;

typedef struct	s_image
{
	void		*ptr;
	char		*add;
	int			bpp;
	int			size_line;
	int			endian;
}				t_image;

typedef struct	s_camera
{
	t_vector	orientation;
	t_image		img;
	t_vector	pov;
	t_vector	right;
	t_vector	up;
	int			fov;
}				t_camera;

typedef struct	s_element
{
	int			id;
	t_vector	point;
	t_color		color;
	t_vector	orientation;
	float		ratio;
	float		diameter;
	float		height;
	t_vector	point2;
	t_vector	point3;
	t_vector	direction;
	float		ref;
	int			nm;
}				t_element;

#endif
