/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:41:17 by snegi             #+#    #+#             */
/*   Updated: 2025/11/19 15:31:17 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	lastcheck(t_cubdata *cd, int i, int j)
{
	int	temp;

	if (cd->map[i][--j] != '1')
		err1("map is not properly walled10\n", cd);
	if (i < cd->map_height - 1
		&& (ft_strlen(cd->map[i]) > ft_strlen(cd->map[i + 1])))
	{
		temp = ft_strlen(cd->map[i + 1]) - 1;
		while (cd->map[i][temp] != '\0' && cd->map[i][temp] != '\n')
		{
			if (cd->map[i][temp++] != '1')
				err1("map is not properly walled11\n", cd);
		}
	}
	if (i > 0 && (ft_strlen(cd->map[i]) > ft_strlen(cd->map[i - 1])))
	{
		temp = ft_strlen(cd->map[i - 1]) - 1;
		while (cd->map[i][temp] != '\0' && cd->map[i][temp] != '\n')
		{
			if (cd->map[i][temp++] != '1')
				err1("map is not properly walled12\n", cd);
		}
	}
}

int	middlecheck(t_cubdata *cd, int i, int j)
{
	int	temp;

	while (cd->map[i][j] == ' ' && cd->map[i][j] != '\0'
		&& cd->map[i][j] != '\n')
	{
		temp = i;
		while (temp < cd->map_height - 1 && cd->map[temp][j] != '1')
		{
			if (cd->map[temp++][j] != ' ')
				err1("map is not properly walled5\n", cd);
		}
		temp = i;
		while (temp > 0 && cd->map[temp][j] != '1')
		{
			if (cd->map[temp--][j] != ' ')
				err1("map is not properly walled6\n", cd);
		}
		j++;
	}
	return (j);
}

int	firstcheck(t_cubdata *cd, int i, int j)
{
	if (cd->map[i][j] == ' ')
	{
		if (j > 0 && cd->map[i][j -1] != '1')
			err1("map is not properly walled2\n", cd);
		if (i > 0 && j > 0 && (cd->map[i - 1][j -1] != '1'
			&& cd->map[i - 1][j - 1] != ' '))
			err1("map is not properly walled3\n", cd);
		if (j > 0 && i < cd->map_height - 1
			&& (cd->map[i + 1][j - 1] != '1' && cd->map[i + 1][j - 1] != ' '))
			err1("map is not properly walled4\n", cd);
		j = middlecheck(cd, i, j);
		if (cd->map[i][j] != '1')
			err1("map is not properly walled7\n", cd);
		if (i > 0 && (cd->map[i - 1][j] != '1' && cd->map[i - 1][j] != ' '))
			err1("map is not properly walled8\n", cd);
		if (i < cd->map_height - 1 && (cd->map[i + 1][j] != '1'
			&& cd->map[i + 1][j] != ' '))
			err1("map is not properly walled9\n", cd);
	}
	return (j);
}

void	checkerrormap(t_cubdata *cd)
{
	int	i;
	int	j;

	i = -1;
	while (cd->map && cd->map[++i])
	{
		if (i == 0 || i == cd->map_height - 1)
			check_firstlastline(cd, i);
		j = -1;
		while (cd->map[i][++j] && cd->map[i][j] != '\0'
			&& cd->map[i][j] != '\n')
		{
			if (cd->map[i][j] == 'N' || cd->map[i][j] == 'S'
				|| cd->map[i][j] == 'W' || cd->map[i][j] == 'E')
			{
				cd->p_x = (double)j + 0.5;
				cd->p_y = (double)i + 0.5;
			}
			if (j == 0 && cd->map[i][j] != '1' && cd->map[i][j] != ' ')
				err1("map is not properly walled1\n", cd);
			j = firstcheck(cd, i, j);
		}
		lastcheck(cd, i, j);
	}
}
