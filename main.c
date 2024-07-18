/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:46:13 by snegi             #+#    #+#             */
/*   Updated: 2024/07/17 15:49:08 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	storecubedata(int fd, char *nextline, t_cubdata *cubdata)
{
	char	*temp;
	int		i;

	i = 0;
	while (nextline)
	{
		temp = get_next_line(fd);
		if (!ft_strncmp(nextline, "NO ", 3))
			cubdata->north = ft_strdup1(nextline + 3);
		else if (!ft_strncmp(nextline, "SO ", 3))
			cubdata->south = ft_strdup1(nextline + 3);
		else if (!ft_strncmp(nextline, "WE ", 3))
			cubdata->west = ft_strdup1(nextline + 3);
		else if (!ft_strncmp(nextline, "EA ", 3))
			cubdata->east = ft_strdup1(nextline + 3);
		else if (!ft_strncmp(nextline, "F ", 2))
			cubdata->floor_color = ft_split(nextline + 2, ',');
		else if (!ft_strncmp(nextline, "C ", 2))
			cubdata->ceiling_color = ft_split(nextline + 2, ',');
		else if (ft_strncmp(nextline, "\n", 1) && ft_strncmp(nextline, "\0", 1))
			cubdata->map[i++] = ft_strdup1(nextline); 
		free(nextline);
		nextline = temp;
	}
}

int	error_check1(int count, char *nextline)
{
	if (ft_strncmp(nextline, "\n", 1) && ft_strncmp(nextline, "\0", 1))
		count++;
	if (count > 0 && count < 5 && ft_strncmp(nextline, "\n", 1)
		&& ft_strncmp(nextline, "\0", 1))
	{
		if (ft_strncmp(nextline, "NO ", 3) && ft_strncmp(nextline, "SO ", 3)
			&& ft_strncmp(nextline, "WE ", 3)
			&& ft_strncmp(nextline, "EA ", 3))
			err("map only identifiers- (NO,SO,WE,EA,F,C)\n");
	}
	else if ((count == 5 || count == 6) && ft_strncmp(nextline, "\n", 1)
		&& ft_strncmp(nextline, "\0", 1))
	{
		if (ft_strncmp(nextline, "F ", 2) && ft_strncmp(nextline, "C ", 2))
			err("map only identifiers- (NO,SO,WE,EA,F,C)\n");
	}
	return (count);
}

void	error_check(int fd, char *nextline, t_cubdata *cubdata)
{
	char	*temp;
	int		count;
	char	player;

	player = '\0';
	count = 0;
	while (nextline)
	{
		temp = get_next_line(fd);
		count = error_check1(count, nextline);
		if (count > 6 && ft_strncmp(nextline, "\n", 1)
			&& ft_strncmp(nextline, "\0", 1))
		{
			player = check_mapdata(nextline, temp);
			if (cubdata->firstposition == '\0')
				cubdata->firstposition = player;
			else if (player != '\0' && cubdata->firstposition != '\0')
				err("Multiple character in map");
		}
		free(nextline);
		nextline = temp;
	}
	if (cubdata->firstposition == '\0')
		err("No player in map");
	cubdata->map_height = count - 6;
}

void	storedata(t_cubdata *cubdata, char *file)
{
	int		fd;
	char	*nextline;

	cubdata->floor_color = NULL;
	cubdata->ceiling_color = NULL;
	cubdata->map = NULL;
	cubdata->map_height = 0;
	cubdata->firstposition = '\0';
	fd = open(file, O_RDONLY);
	if (!fd)
		err("Error opening file\n");
	nextline = get_next_line(fd);
	if (!nextline)
		err("no map\n");
	error_check(fd, nextline, cubdata);
	close(fd);
	fd = open(file, O_RDONLY);
	nextline = get_next_line(fd);
	cubdata->map = malloc(sizeof(char *) * (cubdata->map_height + 1));
	storecubedata(fd, nextline, cubdata);
	cubdata->map[cubdata->map_height] = NULL;
	checkerrormap(cubdata);
	checkcolorerror(cubdata);
	checkpatherror(cubdata);
	close(fd);
}

int	main(int ac, char **ar)
{
	t_data		data;
	t_cubdata	cubdata;

	cubdata.north = NULL;
	cubdata.south = NULL;
	cubdata.east = NULL;
	cubdata.west = NULL;
	if (ac != 2)
		return (printf("put correct map\n"));
	if (ft_strncmp(&ar[1][ft_strlen(ar[1]) - 4], ".cub\0", 5))
		return (printf("put correct map-- format:.cub\n"));
	cubdata.map_height = 0;
	storedata(&cubdata, ar[1]);
	cub3d(&cubdata);
	free_cubdata(&cubdata);
	return (0);
}
