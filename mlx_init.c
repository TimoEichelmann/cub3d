/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:53:22 by snegi             #+#    #+#             */
/*   Updated: 2024/07/18 15:24:44 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_ratios(t_image *img)
{
	if (img->width < img->height)
		img->height = img->width;
	if (img->height < img->width)
		img->width = img->height;
}

void	init_txts(t_data *d, t_cubdata *cd)
{
	d->imgs[0]->img = mlx_xpm_file_to_image
		(d->mlx, cd->north, &d->imgs[0]->width, &d->imgs[0]->height);
	d->imgs[1]->img = mlx_xpm_file_to_image
		(d->mlx, cd->south, &d->imgs[1]->width, &d->imgs[1]->height);
	d->imgs[2]->img = mlx_xpm_file_to_image
		(d->mlx, cd->west, &d->imgs[2]->width, &d->imgs[2]->height);
	d->imgs[3]->img = mlx_xpm_file_to_image
		(d->mlx, cd->east, &d->imgs[3]->width, &d->imgs[3]->height);
}

void	store_images(t_data *d, t_cubdata *cd)
{
	int	i;

	i = 0;
	d->imgs[0] = (t_image *)malloc(sizeof(t_image));
	d->imgs[1] = (t_image *)malloc(sizeof(t_image));
	d->imgs[2] = (t_image *)malloc(sizeof(t_image));
	d->imgs[3] = (t_image *)malloc(sizeof(t_image));
	init_txts(d, cd);
	while (i <= 3)
	{
		check_ratios(d->imgs[i]);
		i++;
	}
	d->imgs[0]->data = (int *)mlx_get_data_addr(d->imgs[0]->img,
			&d->imgs[0]->bpp, &d->imgs[0]->size_l, &d->imgs[0]->endian);
	d->imgs[1]->data = (int *)mlx_get_data_addr(d->imgs[1]->img,
			&d->imgs[1]->bpp, &d->imgs[1]->size_l, &d->imgs[1]->endian);
	d->imgs[2]->data = (int *)mlx_get_data_addr(d->imgs[2]->img, 
			&d->imgs[2]->bpp, &d->imgs[2]->size_l, &d->imgs[2]->endian);
	d->imgs[3]->data = (int *)mlx_get_data_addr(d->imgs[3]->img,
			&d->imgs[3]->bpp, &d->imgs[3]->size_l, &d->imgs[3]->endian);
}
