/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <stdarg.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "elems.h"
# include "keyboard.h"
# include <limits.h>

# define SPHERE 1
# define PLANE 2
# define SQUARE 3
# define CYLINDER 4
# define TRIANGLE 5
# define CIRCLE 6

# define DIFFUSE 10
# define DIRECTIONAL 11

# define THREADS 16
# define MAX_REF 5

# define BMP_FILE_NAME "img.bmp"
# define BMP_FILE_HEADER_SIZE 14
# define BMP_INFO_HEADER_SIZE 40

typedef struct			s_minirt
{
	void				*mlx_ptr;
	void				*win_ptr;
	int					save;
	int					obj_count;
	int					cam_count;
	int					cur_cam;
	int					mouse;
	int					kb;
	int					cur_obj;
	int					nbref;
	int					percent;
	char				*line;
	char				**split;
	float				t;
	float				k;
	float				aspect;
	float				st;
	t_element			*move_obj;
	t_element			*obj;
	t_rez				resolution;
	t_camera			*camera;
	t_list				*objs_list;
	t_list				*cam_list;
	t_list				*light_list;
	t_ambient			ambient;
	t_ray				ray;
	t_vector			vector;
	t_image				image;
	t_color				tmp_color;
	t_color				color;
	int					tr;
}						t_minirt;

typedef struct			s_thread
{
	int					current;
	t_minirt			scene;
}						t_thread;

/*
** apply_lighting
*/

t_color					apply_lights(t_minirt *rt);
t_color					color_shade(t_minirt *rt, \
	t_vector v1, t_vector v2, t_color color);
t_color					intensity(float intensity, t_color color);
t_vector				vector_light(t_element *light, t_vector vector);

/*
** cameras
*/

void					create_cameras(t_minirt *rt);
void					change_camera(t_minirt *rt);
void					choose_camera(t_minirt *rt);

/*
** handle_colors
*/

void					fill_color(t_minirt *rt, int x, int y);
t_color					get_color_average(t_color c1, t_color c2);
t_color					add_color(t_color c1, t_color c2, int max);
t_color					divide_color(t_color color, int average);
t_color					get_color(t_minirt *rt);

/*
** main
*/

void					setup_rt(t_minirt *rt);
void					start_minirt(t_minirt *rt);
void					create_window(t_minirt *rt);
void					handle_threads(t_minirt *rt);

/*
** more_vectors
*/

t_vector				divide_vectors(t_vector vector, float number);
t_vector				multiply_vectors(t_vector vector, float number);

/*
** mouse_input
*/

int						mouse_position(int x, int y, t_minirt *rt);
int						mouse_unclick(int button, int x, int y, t_minirt *rt);
int						mouse_click(int button, int x, int y, t_minirt *rt);

/*
** move_object
*/

void					select_objects(t_minirt *rt);
int						count_objects(t_list *list);
void					move_color(t_minirt *rt, int reset);
void					unselect_objects(t_minirt *rt);

/*
** parse_helpers
*/

void					check_id(t_minirt *rt);
int						check_split(char **split, int max);
t_vector				split_vector(char *str, t_minirt *rt, int orient);
t_color					split_rgb(char *str, t_minirt *rt);

/*
** parse_objects
*/

void					parse_triangle(t_minirt *rt);
void					parse_cylinder(t_minirt *rt);
void					parse_square(t_minirt *rt);
void					parse_plane(t_minirt *rt);
void					parse_sphere(t_minirt *rt);

/*
** parser
*/

void					parse_ambient(t_minirt *rt);
void					parse_resolution(t_minirt *rt);
void					parse_camera(t_minirt *rt);
void					parse_light(t_minirt *rt);
void					parse_file(char *file, t_minirt *rt);

/*
** raytracing
*/

void					raytracing(t_thread *th);
t_vector				calculate_ray(t_minirt *rt, float x, float y);
t_color					ray_intersect(t_minirt *rt);
void					find_objects(t_minirt *rt, t_element *obj, \
	t_vector ori, t_vector dir);

/*
** reflection
*/

int						apply_shadows(t_minirt *rt, \
	t_vector ori, t_vector dir, t_element *light);
void					reflect(t_minirt *rt);
t_color					color_average_intensity(t_color color1, \
	t_color color2, float intens);
t_vector				get_normal_vector(t_minirt *rt, t_vector vector);
t_vector				get_normal_vector_cylinder(t_element \
	*cylinder, t_vector vector);

/*
** solve_objects_2
*/

void					create_square(t_minirt *rt, t_element *cube, \
	t_vector point, t_vector orientation);
void					solve_square(t_minirt *rt, t_element *square, \
	t_vector ori, t_vector dir);
void					solve_triangle(t_minirt *rt, t_element *triangle, \
	t_vector orientation, t_vector dir);
void					solve_sphere(t_minirt *rt, t_element *sphere, \
	t_vector orientation, t_vector dir);

/*
** solve_objects
*/

void					solve_cylinder(t_minirt *rt, t_element *cylinder, \
	t_vector orientation, t_vector dir);
void					create_circle(t_minirt *rt, t_element *cylinder, \
	float t, int generate);
void					solve_circle(t_minirt *rt, t_element *circle, \
	t_vector orientation, t_vector direction);
void					solve_plane(t_minirt *rt, t_element *plane, \
	t_vector orientation, t_vector direction);

/*
** utils_3
*/

void					create_bmp_image(t_minirt *rt, char *name);
void					bmp_header(char **data, t_minirt *rt);
void					bmp_info(int fd, t_minirt *rt);

/*
** utils_2
*/

int						check_orientation(t_vector *vector);
void					redraw_window(t_minirt *rt);
void					show_controls(t_minirt *rt);
int						count_split(char **split);
t_element				*element_cpy(t_element *elem, t_minirt *rt);

/*
** utils
*/

int						full_exit(t_minirt *rt);
void					error(char *str, t_minirt *rt);
char					**free_split(char **split);
float					ft_atofloat(char *str);
int						get_keypress(int key, t_minirt *rt);

/*
** vectors
*/

t_vector				add_vectors(t_vector vector1, \
	t_vector vector2);
float					vector_length(t_vector vector);
t_vector				subtract_vectors(t_vector vector1, \
	t_vector vector2);
t_vector				cross_vector(t_vector vector1, t_vector vector2);
t_vector				normalize_vector(t_vector vector);
float					get_point(t_vector vector1, t_vector vector2);

/*
** handle_keys
*/

int						handle_key(int key, t_minirt *rt);

#endif
