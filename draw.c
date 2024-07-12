/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:52:01 by teichelm          #+#    #+#             */
/*   Updated: 2024/07/12 16:51:57 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pxl_pos(t_data *img, int x, int y, int color)
{
	char	*pxl;
	int		i;

	i = img->bpb - 8;
	pxl = img->addr + (((img->bpb / 8) * x) + (img->sl * y));
	while (i >= 0)
	{
		if (img->endian == 1)
			*pxl++ = (color >> i) & 0xFF;
		else
			*pxl++ = (color >> ((img->bpb - 8) - i)) & 0xFF;
		i = i - 8;
	}
}

void	draw_verline(t_data *data, int x, int line_height, int side)
{
	int	i;
	int	color;

	if (side == 1)
		color = 0x00FF00;
	else
		color = 0xFF0000;
	if (line_height > SCREEN_HEIGHT)
		line_height = SCREEN_HEIGHT;
	i = SCREEN_HEIGHT / 2;
	i -= line_height / 2;
	while (i < SCREEN_HEIGHT / 2 + (line_height / 2))
	{
		ft_pxl_pos(data, x, i, color);
		i++;
	}
}