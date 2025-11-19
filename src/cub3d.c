/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:13:33 by teichelm          #+#    #+#             */
/*   Updated: 2025/11/19 15:31:17 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	algorithm(void *pl)
{
	struct timeval	t1;
	struct timeval	t2;
	double			dtime;
	t_player		*p;

	p = (t_player *)pl;
	gettimeofday(&t1, NULL);
	reset_image(p->data, p, 0);
	reset_image(p->data, p, 1);
	dda(p);
	mlx_put_image_to_window(p->data->mlx, p->data->win, p->data->img, 0, 0);
	gettimeofday(&t2, NULL);
	dtime = ((t2.tv_sec - t1.tv_sec) * M + (t2.tv_usec - t1.tv_usec)) / M;
	p->move_speed = 5.0 * dtime;
	if (p->move_speed > 1)
		p->move_speed = 0.1;
	p->rot_speed = 3.0 * dtime;
	if (p->rot_speed > 1)
		p->rot_speed = 0.3;
	update(p);
	gettimeofday(&t1, NULL);
	usleep(1000000 / 30);
	return (0);
}

int	cub3d(t_cubdata *cdata)
{
	t_player	*p;
	t_data		*data;

	data = malloc(sizeof(t_data));
	p = start_values(cdata);
	p->data = data;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	store_images(p->data, cdata);
	p->cubdata = cdata;
	data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpb, &data->sl, &data->e);
	dda(p);
	mlx_put_image_to_window(p->data->mlx, p->data->win, p->data->img, 0, 0);
	mlx_loop_hook(data->mlx, algorithm, p);
	mlx_hook(data->win, 2, 1L << 0, movement, p);
	mlx_hook(data->win, 17, 0, ft_free, p);
	mlx_loop(data->mlx);
	return (0);
}
