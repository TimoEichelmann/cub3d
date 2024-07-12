/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:31:06 by snegi             #+#    #+#             */
/*   Updated: 2024/07/12 12:56:33 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	err(char *str)
{
	while(*str)
		write(2, str++, 1);
	exit (1);
}

void	free_cubdata(t_cubdata *cubdata)
{
	int i;

	i = 0;
	if (cubdata ->north)
		free(cubdata->north);
	if (cubdata ->south)
		free(cubdata->south);
	if (cubdata ->west)
		free(cubdata->west);
	if (cubdata ->east)
		free(cubdata->east);
	while (cubdata->ceiling_color && cubdata->ceiling_color[i])
		free(cubdata->ceiling_color[i++]);
	free(cubdata->ceiling_color);
	i = 0;
	while (cubdata->floor_color && cubdata->floor_color[i])
		free(cubdata->floor_color[i++]);
	free(cubdata->floor_color);
	i = 0;
	while (cubdata->map && cubdata->map[i])
		free(cubdata->map[i++]);
	free(cubdata->map);
}

void	err1(char *str, t_cubdata *cubdata)
{
	while(*str)
		write(2, str++, 1);
	free_cubdata(cubdata);
	exit (1);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		on_destroy(data);
	return (0);
}

int	on_destroy(t_data *data)
{
	int	index;

	index = 0;
	// free_cubdata(data->cubdata);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}