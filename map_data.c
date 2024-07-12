/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:35:27 by snegi             #+#    #+#             */
/*   Updated: 2024/07/12 16:50:24 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	check_mapdata(char *line, char *temp)
{
	int i;
	char position;
	int count;

	i = -1;
	count = 0;
	position = '\0';
	while  (line[++i] && line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != ' ' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			err("map is not in correct format\n");
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			count++;
			position = line[i];
		}
		if (count > 1)
			err("map is not in correct format\n");
	}

	i = -1;
	while  (temp && temp[++i] && temp[i] != '\0' && temp[i] != '\n')
	{
		if (temp[i] != '0' && temp[i] != ' ' && temp[i] != '1' && temp[i] != 'N' && temp[i] != 'S' && temp[i] != 'E' && temp[i] != 'W')
			err("map is not in correct format\n");
	}
	return position;
}

void	check_firstlastline(t_cubdata *cubdata, int i)
{
	int	j;
	int k;

	j = 0;
	while (cubdata->map[i][j]  && cubdata->map[i][j] != '\0' && cubdata->map[i][j] != '\n')
	{
		k = i;
		if (cubdata->map[i][j] != '1' && cubdata->map[i][j] != ' ')
			err1("map is not properly walled\n", cubdata);
		if (cubdata->map[i][j] == ' ' && i == 0)
		{
			while (k < cubdata->map_height - 1 && cubdata->map[k][j] != '1')
			{
				if (cubdata->map[k++][j] != ' ')
					err1("map is not properly walled\n", cubdata);
			}
		}
		else if (cubdata->map[i][j] == ' ' && i > 0)
		{
			while (k > 0 && cubdata->map[k][j] != '1')
			{
				if (cubdata->map[k--][j] != ' ')
					err1("map is not properly walled\n", cubdata);
			}
		}
		j++;
	}
}

void	checkerrormap(t_cubdata *cubdata)
{
	int i;
	int j;
	int temp;

	i = 0;
	while (cubdata->map && cubdata->map[i])
	{
		if (i == 0 || i == cubdata->map_height - 1)
			check_firstlastline(cubdata, i);
		j = 0;
		while (cubdata->map[i][j]  && cubdata->map[i][j] != '\0' && cubdata->map[i][j] != '\n')
		{
			if (cubdata->map[i][j] == 'N' || cubdata->map[i][j] == 'S' || cubdata->map[i][j] == 'W' || cubdata->map[i][j] == 'E')
			{
				cubdata->p_y = i + 0.5;
				cubdata->p_x = j + 0.5;
			}
			if (j == 0 && cubdata->map[i][j] != '1' && cubdata->map[i][j] != ' ')
				err1("map is not properly walled1\n", cubdata);
			if (cubdata->map[i][j] == ' ')
			{
				if (j > 0 && cubdata->map[i][j -1] != '1')
					err1("map is not properly walled2\n", cubdata);
				if (i > 0 && j > 0 && (cubdata->map[i - 1][j -1] != '1' && cubdata->map[i - 1][j - 1] != ' '))
					err1("map is not properly walled3\n", cubdata);
				if (j > 0 && i < cubdata->map_height - 1 && (cubdata->map[i + 1][j - 1] != '1' && cubdata->map[i + 1][j - 1] != ' '))
					err1("map is not properly walled4\n", cubdata);
				while (cubdata->map[i][j] == ' ' && cubdata->map[i][j] != '\0' && cubdata->map[i][j] != '\n')
				{
					temp = i;
					while (temp < cubdata->map_height - 1 && cubdata->map[temp][j] != '1')
					{
						if (cubdata->map[temp++][j] != ' ')
							err1("map is not properly walled5\n", cubdata);
					}
					temp = i;
					while (temp > 0 && cubdata->map[temp][j] != '1')
					{
						if (cubdata->map[temp--][j] != ' ')
							err1("map is not properly walled6\n", cubdata);
					}
					j++;
				}
				if (cubdata->map[i][j] != '1')
					err1("map is not properly walled7\n", cubdata);
				if (i > 0 && (cubdata->map[i - 1][j] != '1' && cubdata->map[i - 1][j] != ' '))
					err1("map is not properly walled8\n", cubdata);
				if ( i < cubdata->map_height - 1 && (cubdata->map[i + 1][j] != '1' && cubdata->map[i + 1][j] != ' '))
					err1("map is not properly walled9\n", cubdata);
			}
			j++;
		}
		if (cubdata->map[i][--j] != '1')
				err1("map is not properly walled10\n", cubdata);
		if (i < cubdata->map_height - 1  && (ft_strlen(cubdata->map[i]) > ft_strlen(cubdata->map[i + 1])))
		{
			temp = ft_strlen(cubdata->map[i + 1]) - 1;
			while (cubdata->map[i][temp] != '\0' && cubdata->map[i][temp] != '\n')
			{
				if(cubdata->map[i][temp++] != '1')
					err1("map is not properly walled11\n", cubdata);
			}
		}
		if ( i > 0 && ft_strlen(cubdata->map[i]) > ft_strlen(cubdata->map[i - 1]))
		{
			temp = ft_strlen(cubdata->map[i - 1]) - 1;
			while (cubdata->map[i][temp] != '\0' && cubdata->map[i][temp] != '\n')
			{
				if(cubdata->map[i][temp++] != '1')
					err1("map is not properly walled12\n", cubdata);
			}
		}
		i++;
	}
}