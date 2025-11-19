/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:29:00 by teichelm          #+#    #+#             */
/*   Updated: 2025/11/19 15:31:17 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_free(void *pl)
{
	t_player	*p;

	p = (t_player *)pl;
	mlx_destroy_image(p->data->mlx, p->data->imgs[0]->img);
	mlx_destroy_image(p->data->mlx, p->data->imgs[1]->img);
	mlx_destroy_image(p->data->mlx, p->data->imgs[2]->img);
	mlx_destroy_image(p->data->mlx, p->data->imgs[3]->img);
	free(p->data->imgs[3]);
	free(p->data->imgs[2]);
	free(p->data->imgs[1]);
	free(p->data->imgs[0]);
	mlx_destroy_image(p->data->mlx, p->data->img);
	mlx_clear_window(p->data->mlx, p->data->win);
	mlx_destroy_window(p->data->mlx, p->data->win);
	mlx_destroy_display(p->data->mlx);
	free(p->data->mlx);
	free(p->data);
	free_cubdata(p->cubdata);
	free(p);
	exit (0);
}
