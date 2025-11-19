/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:52:01 by teichelm          #+#    #+#             */
/*   Updated: 2025/11/19 15:31:17 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_color(char **color)
{
	int	r;
	int	g;
	int	b;

	r = atoi(color[0]);
	g = atoi(color[1]);
	b = atoi(color[2]);
	return ((r << 16) | (g << 8) | b);
}

void	reset_image(t_data *img, t_player *p, int ind)
{
	int	i;
	int	j;
	int	height;

	i = 0;
	j = 0;
	height = SCREEN_HEIGHT / 2;
	if (ind == 1)
	{
		j = SCREEN_HEIGHT / 2;
		height = SCREEN_HEIGHT;
	}
	while (j < height)
	{
		while (i < SCREEN_WIDTH)
		{
			if (ind == 1)
				ft_pxl_pos(img, i, j, get_color(p->cubdata->floor_color));
			else
				ft_pxl_pos(img, i, j, get_color(p->cubdata->ceiling_color));
			i++;
		}
		j++;
		i = 0;
	}
}

void	ft_pxl_pos(t_data *img, int x, int y, int color)
{
	char	*pxl;
	int		i;

	i = img->bpb - 8;
	pxl = img->addr + (((img->bpb / 8) * x) + (img->sl * y));
	while (i >= 0)
	{
		if (img->e == 1)
			*pxl++ = (color >> i) & 0xFF;
		else
			*pxl++ = (color >> ((img->bpb - 8) - i)) & 0xFF;
		i = i - 8;
	}
}
