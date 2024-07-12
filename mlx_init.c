/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:53:22 by snegi             #+#    #+#             */
/*   Updated: 2024/07/12 12:56:49 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    window_create(t_data *data)
{
    t_cubdata *cubdata;
    int w_x;
    int w_y;

    w_x = 1920;
    w_y = 1080;
    // cubdata = data->cubdata;
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, w_x, w_y, "./cub3d");
    mlx_key_hook(data->win, key_hook, data);
    mlx_hook(data->win, 17, 0, on_destroy, data);
    mlx_loop(data->mlx);
}