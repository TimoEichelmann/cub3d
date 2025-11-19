/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:56:26 by teichelm          #+#    #+#             */
/*   Updated: 2025/11/19 15:31:17 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	position_change(t_player *p, int sign)
{
	p->posx += sign * (p->dirx * p->move_speed);
	p->posy += sign * (p->diry * p->move_speed);
	if (p->cubdata->map[(int)floor(p->posy)][(int)floor(p->posx)]
		&& p->cubdata->map[(int)floor(p->posy)][(int)floor(p->posx)] == '1')
	{
		p->posx -= sign * (p->dirx * p->move_speed);
		p->posy -= sign * (p->diry * p->move_speed);
	}
	p->move_f = 0;
	p->move_b = 0;
}

void	rotation(t_player *p, int s)
{
	double	r_speed;
	double	olddirx;
	double	oldplanex;

	r_speed = p->rot_speed;
	olddirx = p->dirx;
	p->dirx = p->dirx * cos(s * r_speed) - p->diry * sin(s * r_speed);
	p->diry = olddirx * sin(s * r_speed) + p->diry * cos(s * r_speed);
	oldplanex = p->planex;
	p->planex = p->planex * cos(s * r_speed) - p->planey * sin(s * r_speed);
	p->planey = oldplanex * sin(s * r_speed) + p->planey * cos(s * r_speed);
	p->rotate_l = 0;
	p->rotate_r = 0;
}

void	update(t_player *p)
{
	if (p->move_f == 1)
		position_change(p, 1);
	if (p->move_b == 1)
		position_change(p, -1);
	if (p->rotate_l == 1 
		&& p->cubdata->firstposition != 'W' && p->cubdata->firstposition != 'E')
		rotation(p, 1);
	if (p->rotate_r == 1 
		&& p->cubdata->firstposition != 'W' && p->cubdata->firstposition != 'E')
		rotation(p, -1);
	if (p->rotate_l == 1 
		&& (p->cubdata->firstposition == 'W'
			|| p->cubdata->firstposition == 'E'))
		rotation(p, -1);
	if (p->rotate_r == 1 
		&& (p->cubdata->firstposition == 'W'
			|| p->cubdata->firstposition == 'E'))
		rotation(p, 1);
	return ;
}

int	movement(int keycode, void *player)
{
	t_player	*p;

	p = (t_player *)player;
	if (keycode == XK_Down || keycode == XK_s)
		p->move_b = 1;
	if (keycode == XK_Up || keycode == XK_w)
		p->move_f = 1;
	if (keycode == XK_Left || keycode == XK_a)
		p->rotate_r = 1;
	if (keycode == XK_Right || keycode == XK_d)
		p->rotate_l = 1;
	if (keycode == XK_Escape)
		ft_free(p);
	return (0);
}
