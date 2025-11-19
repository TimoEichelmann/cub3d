/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:31:06 by snegi             #+#    #+#             */
/*   Updated: 2025/11/19 15:31:17 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	err(char *str, char *fr, char *fr2)
{
	while (*str)
		write(2, str++, 1);
	if (fr2)
		free(fr2);
	if (fr)
		free(fr);
	exit (1);
}

void	free_cubdata(t_cubdata *cubdata)
{
	int	i;

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
	while (*str)
		write(2, str++, 1);
	free_cubdata(cubdata);
	exit (1);
}

void	checkcolorerror(t_cubdata *cubdata)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	j = 0;
	while (cubdata->ceiling_color && cubdata->ceiling_color[i]
		&& cubdata->ceiling_color[i] != NULL)
	{
		temp = ft_atoi1(cubdata->ceiling_color[i++]);
		if (temp < 0 || temp > 255)
			err1("Incorrect ceiling colors\n", cubdata);
	}
	while (cubdata->floor_color && cubdata->floor_color[j]
		&& cubdata->floor_color[j] != NULL)
	{
		temp = ft_atoi1(cubdata->floor_color[j++]);
		if (temp < 0 || temp > 255)
			err1("Incorrect floor colors\n", cubdata);
	}
	if (i != 3 || j != 3)
		err1("Incorrect floor/ceiling colors\n", cubdata);
}

void	checkpatherror(t_cubdata *cubdata)
{
	int	fd;

	fd = open(cubdata->north, R_OK);
	if (fd == -1)
		err1("north texture path is incorrect\n", cubdata);
	close(fd);
	fd = open(cubdata->south, R_OK);
	if (fd == -1)
		err1("south texture path is incorrect\n", cubdata);
	close(fd);
	fd = open(cubdata->west, R_OK);
	if (fd == -1)
		err1("west texture path is incorrect\n", cubdata);
	close(fd);
	fd = open(cubdata->east, R_OK);
	if (fd == -1)
		err1("east texture path is incorrect\n", cubdata);
	close(fd);
}
