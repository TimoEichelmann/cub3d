/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:54:14 by teichelm          #+#    #+#             */
/*   Updated: 2024/07/18 16:55:08 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_wallx(t_dda *dda, t_player *p, int txtwidth)
{
	double	wallx;

	wallx = 0;
	if (dda->side == 0)
	{
		wallx += p->posy + (dda->perpwalldist * dda->raydiry);
		if (dda->raydiry == 1e30)
			wallx = p->posy;
	}
	else
	{
		wallx += p->posx + (dda->perpwalldist * dda->raydirx);
		if (dda->raydirx == 1e30)
			wallx = p->posx;
	}
	wallx -= floor(wallx);
	return ((int)(wallx * txtwidth));
}

double	step(int line_length, int txtheight)
{
	return (1.0 * txtheight / line_length);
}

void	mirror_txt(t_dda *dda, int *txx, int txtwidth)
{
	if (dda->side == 0 && dda->raydirx > 0)
		*txx = txtwidth - *txx - 1;
	if (dda->side == 1 && dda->raydiry < 0)
		*txx = txtwidth - *txx - 1;
}

void	textured_line(int line_length, t_image *txt, t_player *p, t_dda *dda)
{
	int		start;
	int		end;
	int		txx;
	double	txtpos;
	int		txy;

	start = -line_length / 2 + SCREEN_HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = line_length / 2 + SCREEN_HEIGHT / 2;
	if (end > SCREEN_HEIGHT)
		end = SCREEN_HEIGHT;
	txx = ft_wallx(dda, p, txt->width);
	mirror_txt(dda, &txx, txt->width);
	txtpos = (start - SCREEN_HEIGHT / 2 + line_length / 2)
		* step(line_length, txt->height);
	while (start < end)
	{
		txy = (int)txtpos & (txt->height - 1);
		txtpos += step(line_length, txt->height);
		ft_pxl_pos(p->data, dda->x, start, txt->data[txt->height * txy + txx]);
		start++;
	}
}

void	paint_wall(t_dda *dda, t_player *p)
{
	int		line_height;

	if (dda->side == 0)
		dda->perpwalldist = fabs(dda->sidedistx - dda->deldistx);
	else
		dda->perpwalldist = fabs(dda->sidedisty - dda->deldisty);
	line_height = (SCREEN_HEIGHT / dda->perpwalldist);
	if (dda->side == 0 && dda->raydirx < 0)
		textured_line(line_height, p->data->imgs[3], p, dda);
	else if (dda->side == 0 && dda->raydirx > 0)
		textured_line(line_height, p->data->imgs[2], p, dda);
	else if (dda->side == 1 && dda->raydiry < 0)
		textured_line(line_height, p->data->imgs[1], p, dda);
	else if (dda->side == 1 && dda->raydiry > 0)
		textured_line(line_height, p->data->imgs[0], p, dda);
}

//sequence for if statements : E W S N