/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:35:27 by snegi             #+#    #+#             */
/*   Updated: 2024/07/18 15:37:14 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_mapdata1(char *temp)
{
	int	i;

	i = -1;
	while (temp && temp[++i] && temp[i] != '\0' && temp[i] != '\n')
	{
		if (temp[i] != '0' && temp[i] != ' ' && temp[i] != '1' && temp[i] != 'N'
			&& temp[i] != 'S' && temp[i] != 'E' && temp[i] != 'W')
			err("only allowed (1,0,S,N,W,E and space)1\n");
	}
}

char	check_mapdata(char *li, char *temp)
{
	int		i;
	char	position;
	int		count;

	i = -1;
	count = 0;
	position = '\0';
	if (li[0] == '\n')
		err("empty line is not allowd inside the map\n");
	while (li[++i] && li[i] != '\0' && li[i] != '\n')
	{
		if (li[i] != '0' && li[i] != ' ' && li[i] != '1' && li[i] != 'N'
			&& li[i] != 'S' && li[i] != 'E' && li[i] != 'W')
			err("only allowed (1,0,S,N,W,E and space)2\n");
		if (li[i] == 'N' || li[i] == 'S' || li[i] == 'E' || li[i] == 'W')
		{
			count++;
			position = li[i];
		}
		if (count > 1)
			err("more than 1 player position\n");
	}
	check_mapdata1(temp);
	return (position);
}

void	check_lastborder(t_cubdata *cd, int k, int j)
{
	while (k > 0 && cd->map[k][j] != '1')
	{
		if (cd->map[k--][j] != ' ')
			err1("map is not properly walled\n", cd);
	}
}

void	check_firstlastline(t_cubdata *cd, int i)
{
	int	j;
	int	k;

	j = -1;
	while (cd->map[i][++j] && cd->map[i][j] != '\0' && cd->map[i][j] != '\n')
	{
		k = i;
		if (cd->map[i][j] != '1' && cd->map[i][j] != ' ')
			err1("map is not properly walled\n", cd);
		if (cd->map[i][j] == ' ' && i == 0)
		{
			while (k < cd->map_height - 1 && cd->map[k][j] != '1')
			{
				if (cd->map[k++][j] != ' ')
					err1("map is not properly walled\n", cd);
			}
		}
		else if (cd->map[i][j] == ' ' && i > 0)
			check_lastborder(cd, k, j);
	}
}
