/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:57:03 by teichelm          #+#    #+#             */
/*   Updated: 2025/11/19 15:31:17 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_steps(t_dda *dda, t_player *p)
{
	if (dda->raydirx < 0)
	{
		dda->sidedistx = (p->posx - dda->mapx) * dda->deldistx;
		dda->stepx = -1;
	}
	else
	{
		dda->sidedistx = (dda->mapx + 1.0 - p->posx) * dda->deldistx;
		dda->stepx = 1;
	}
	if (dda->raydiry < 0)
	{
		dda->sidedisty = (p->posy - dda->mapy) * dda->deldisty;
		dda->stepy = -1;
	}
	else
	{
		dda->sidedisty = (dda->mapy + 1.0 - p->posy) * dda->deldisty;
		dda->stepy = 1;
	}
}

void	init_dda(t_player *p, t_dda *dda, int x)
{
	dda->camx = -1 * (2 * x / (double)SCREEN_WIDTH - 1);
	dda->raydirx = p->dirx + (p->planex * dda->camx);
	dda->raydiry = p->diry + (p->planey * dda->camx);
	dda->deldistx = fabs(1.0 / dda->raydirx);
	dda->deldisty = fabs(1.0 / dda->raydiry);
	dda->mapx = (int)p->posx;
	dda->mapy = (int)p->posy;
	init_steps(dda, p);
}
