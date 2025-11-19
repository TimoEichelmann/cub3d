/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:52:00 by teichelm          #+#    #+#             */
/*   Updated: 2025/11/19 15:31:17 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	orientation(t_cubdata *d, t_player *p, int sign)
{
	if (d->firstposition == 'W' || d->firstposition == 'E')
	{
		p->planex = 0;
		p->planey = 0.66 * sign;
		p->dirx = 1 * sign;
		p->diry = 0;
	}
	else
	{
		p->planex = 0.66 * sign;
		p->planey = 0;
		p->diry = 1 * sign;
		p->dirx = 0;
	}
}

t_player	*start_values(t_cubdata *d)
{
	t_player	*p;
	int			sign;

	sign = -1;
	if (d->firstposition == 'E' || d->firstposition == 'S')
		sign = 1;
	p = malloc(sizeof(t_player));
	orientation(d, p, sign);
	p->end = 0;
	p->posx = d->p_x;
	p->posy = d->p_y;
	p->time = 0;
	p->old_time = 0;
	p->rotate_r = 0;
	p->rotate_l = 0;
	p->move_b = 0;
	p->move_f = 0;
	return (p);
}

void	step_dir(t_dda *dda)
{
	if (dda->sidedistx < dda->sidedisty)
	{
		dda->sidedistx += dda->deldistx;
		dda->mapx += dda->stepx;
		dda->side = 0;
	}
	else
	{
		dda->sidedisty += dda->deldisty;
		dda->mapy += dda->stepy;
		dda->side = 1;
	}
}

void	dda(t_player *p)
{
	t_dda	dda;

	dda.x = 0;
	while (dda.x < SCREEN_WIDTH)
	{
		dda.hit = 0;
		init_dda(p, &dda, dda.x);
		while (dda.hit == 0)
		{
			step_dir(&dda);
			if (p->cubdata->map[dda.mapy][dda.mapx] == '1')
				dda.hit = 1;
		}
		paint_wall(&dda, p);
		dda.x++;
	}
}
