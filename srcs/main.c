/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgontier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 16:32:16 by tgontier          #+#    #+#             */
/*   Updated: 2020/05/23 10:49:27 by tgontier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** Sets the struct elements to the right starting value,
** gets the correct vectors using the corresponding functions.
*/

void			setup_rt(t_minirt *rt)
{
	rt->ray.orientation = (t_vector){rt->camera->pov.x, \
		rt->camera->pov.y, rt->camera->pov.z};
	rt->aspect = (float)rt->resolution.x / (float)rt->resolution.y;
	rt->camera->up = (t_vector){0, -1, 0};
	rt->camera->right = cross_vector(normalize_vector(\
		rt->camera->orientation), rt->camera->up);
	rt->camera->up = cross_vector(rt->camera->right, \
		normalize_vector(rt->camera->orientation));
	rt->k = 0;
	rt->t = 0;
}

/*
** Creates the threads which will handle the process, and
** sends to the raytracing function.
*/

void			handle_threads(t_minirt *rt)
{
	int			i;
	pthread_t	thr[THREADS];
	t_thread	buf[THREADS];

	i = 0;
	while (i < THREADS)
	{
		buf[i].current = i;
		ft_memcpy(&buf[i].scene, rt, sizeof(t_minirt));
		buf[i].scene.tr = i;
		pthread_create(&thr[i], NULL, (void*)raytracing, &buf[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(thr[i], NULL);
		i++;
	}
}

/*
** Mlx functions that start the window and send to the functions
** that will handle events.
*/

void			create_window(t_minirt *rt)
{
	if (!(rt->win_ptr = mlx_new_window(rt->mlx_ptr, rt->resolution.x,
		rt->resolution.y, "miniRT")))
		error("fail to create Minilibx window", rt);
	mlx_hook(rt->win_ptr, 2, 0, get_keypress, rt);
	mlx_hook(rt->win_ptr, 4, 0, mouse_click, rt);
	mlx_hook(rt->win_ptr, 5, 0, mouse_unclick, rt);
	mlx_hook(rt->win_ptr, 6, 0, mouse_position, rt);
	mlx_hook(rt->win_ptr, 17, 0, full_exit, rt);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, \
		rt->camera->img.ptr, 0, 0);
	mlx_loop(rt->mlx_ptr);
}

/*
** Checks for the --save option, starts the process.
*/

void			start_minirt(t_minirt *rt)
{
	create_cameras(rt);
	choose_camera(rt);
	if (rt->save)
	{
		create_bmp_image(rt, BMP_FILE_NAME);
		full_exit(rt);
	}
	create_window(rt);
}

int				main(int argc, char **argv)
{
	t_minirt	rt;

	ft_bzero(&rt, sizeof(t_minirt));
	if (!(rt.mlx_ptr = mlx_init()))
		error("fail to initialize Minilibx", &rt);
	if (argc > 3 || argc == 1 || (argc == 3 && !ft_strequ(argv[2], "--save")))
		error("wrong arguments", &rt);
	if (argc == 3 && ft_strequ(argv[2], "--save"))
		rt.save = 1;
	if (!ft_str_end(argv[1], ".rt"))
		error("wrong file extension", &rt);
	parse_file(argv[1], &rt);
	start_minirt(&rt);
	return (1);
}
