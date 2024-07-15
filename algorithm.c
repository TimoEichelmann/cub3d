/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timo <timo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:13:33 by teichelm          #+#    #+#             */
/*   Updated: 2024/07/15 21:27:57 by timo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	*start_values(t_cubdata *d)
{
	t_player	*p;
	int			sign;

	sign = 1;
	if (d->firstposition == 'E' || d->firstposition == 'S')
		sign = -1;
	p = malloc(sizeof(t_player));
	if (d->firstposition == 'W' || d->firstposition == 'E')
	{
		p->planex = 0;
		p->planey = 1 * sign;
		p->dirx = 1 * sign;
		p->diry = 0;
	}
	else
	{
		p->planex = 1 * sign;
		p->planey = 0;
		p->diry = 1 * sign;
		p->dirx = 0;
	}
	p->end = 0;
	p->posx = d->p_x;
	p->posy = d->p_y;
	p->time = 0;
	p->old_time = 0;
	p->move_b = 0;
	p->move_f = 0;
	return (p);
}

void	dda(t_player *p, t_cubdata *d, t_data *data)
{
	int		x;
	t_dda	dda;
	int		line_height;

	x = 0;
	while (x <= SCREEN_WIDTH)
	{
		dda.hit = 0;
		dda.camx = 2 * x / (double)SCREEN_WIDTH - 1;
		dda.raydirx = p->dirx + (p->planex * dda.camx);
		dda.raydiry = -1 * p->diry + (p->planey * dda.camx);
		if (dda.raydirx == 0)
			dda.raydirx = 1e30;
		if (dda.raydiry == 0)
			dda.raydiry = 1e30;
		dda.deldistx = fabs(1.0 / dda.raydirx);
		dda.deldisty = fabs(1.0 / dda.raydiry);
		dda.mapx = (int)p->posx;
		dda.mapy = (int)p->posy;
		if (dda.raydirx < 0)
		{
			dda.sidedistx = (p->posx - dda.mapx) * dda.deldistx;
			dda.stepx = -1;
		}
		else
		{
			dda.sidedistx = (dda.mapx + 1.0 - p->posx) * dda.deldistx;
			dda.stepx = 1;
		}
		if (dda.raydiry < 0)
		{
			dda.sidedisty = (p->posy - dda.mapy) * dda.deldisty;
			dda.stepy = -1;
		}
		else
		{
			dda.sidedisty = (dda.mapy + 1.0 - p->posy) * dda.deldisty;
			dda.stepy = 1;
		}
		// if (x == 450)
		// 	printf("%f %f %f %f\n", dda.sidedistx, dda.deldistx, dda.deldisty, dda.sidedisty);
		while (dda.hit == 0)
		{
			if (dda.sidedistx <= dda.sidedisty && dda.raydirx != 1e30)
			{
				dda.sidedistx += dda.deldistx;
				dda.mapx += dda.stepx;
				dda.side = 0;
			}
			else
			{
				dda.sidedisty += dda.deldisty;
				dda.mapy += dda.stepy;
				dda.side = 1;
			}
			// if (x == 450)
			// 	printf("pos: (%d|%d) %c\n", dda.mapx, dda.mapy, d->map[dda.mapy][dda.mapx]);
			if (d->map[dda.mapy][dda.mapx] > '0')
				dda.hit = 1;
		}
		// if (x == 450)
		// {
		// 	printf("%f   %f %d\n", dda.sidedistx, dda.sidedisty, dda.side);
		// }
		if (dda.side == 0)
			dda.perpwalldist = dda.sidedistx - dda.deldistx;
		else
			dda.perpwalldist = dda.sidedisty - dda.deldisty;
		line_height = (SCREEN_HEIGHT / dda.perpwalldist);
		// if (x == 450)
		// {
		// 	printf("pos: (%d|%d) %c\n", dda.mapx, dda.mapy, d->map[dda.mapy][dda.mapx]);
		// 	printf("%f\n", dda.perpwalldist);
		// }
		draw_verline(data, x, line_height, dda.side);
		x++;
	}
}

int	movement(int keycode, void *player)
{
	t_player *p;

	
	p = (t_player *)player;
	if (keycode == 0xff54)
		p->move_b = 1;
	if (keycode == 0xff52)
		p->move_f = 1;
	return (0);
}

void	update(t_player *p)
{
	if (p->move_f == 1)
	{
		p->posx += p->dirx * p->move_speed;
		p->posy += p->diry * p->move_speed;
		p->move_f = 0;
	}
	if (p->move_b == 1)
	{
		p->posx -= p->dirx * p->move_speed;
		p->posy -= p->diry * p->move_speed;
	 	p->move_b = 0;
	}
}

int algorithm(void *pl)
{
	struct timeval	start;
	struct timeval	end;
	double			delta_time;
	t_player		*p;

	p = (t_player *)pl;
	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&end, NULL);
		delta_time = ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec)) / 1000000.0;
		p->move_speed = 5.0 * delta_time;
		p->rot_speed = 3.0 * delta_time;
		update(p);
		dda(p, p->cubdata, p->data);
		mlx_put_image_to_window(p->data->mlx, p->data->win, p->data->img, 0, 0);
		gettimeofday(&start, NULL);
		usleep(1000000 / 30);
	}
	return (0);
}

int game(t_cubdata *cdata)
{
	t_player	*p;
	t_data		*data;

	data = malloc(sizeof(t_data));
	p = start_values(cdata);
	p->cubdata = cdata;
	p->data = data;
	data->addr = NULL;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpb, &data->sl, &data->endian);
	dda(p, cdata, data);
	mlx_put_image_to_window(p->data->mlx, p->data->win, p->data->img, 0, 0);
	mlx_loop_hook(data->mlx, algorithm, p);
	mlx_key_hook(data->win, movement, p);
	mlx_loop(data->mlx);
}