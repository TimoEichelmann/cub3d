/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:54:29 by snegi             #+#    #+#             */
/*   Updated: 2024/07/24 15:57:54 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*findline(char *res)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!res)
		return (NULL);
	while (res[i] != '\n' && res[i] != '\0')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	i = 0;
	while (res[i] != '\n' && res[i] != '\0')
	{
		line[i] = res[i];
		i++;
	}
	line[i] = res[i];
	line[++i] = '\0';
	return (line);
}

char	*readfile(int fd, char *res, char *buf)
{
	ssize_t	char_read;
	char	*temp;

	if (!buf)
		return (NULL);
	char_read = read(fd, buf, BUFFER_SIZE);
	while (char_read > 0 && buf[0] != '\0')
	{
		buf[char_read] = '\0';
		temp = res;
		res = ft_strjoin(temp, buf);
		free(temp);
		if (ft_strchr(buf, '\n'))
			return (res);
		else
			char_read = read(fd, buf, BUFFER_SIZE);
	}
	if (char_read < 0)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

char	*final(char *res, char *temp, char *line)
{
	int		i;
	int		j;

	i = 0;
	i = ft_strlen(line);
	j = ft_strlen(temp);
	if (i == j)
	{
		free (temp);
		res = NULL;
		return (NULL);
	}
	res = malloc(sizeof(char) * (j - i + 1));
	j = 0;
	while (temp[i] != '\0')
		res[j++] = temp[i++];
	res[j] = '\0';
	free(temp);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*res = NULL;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		free(res);
		res = NULL;
		return (NULL);
	}
	line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	temp = readfile(fd, res, line);
	free(line);
	if (!temp)
		return (NULL);
	if (temp[0] == '\0')
	{
		free(temp);
		res = NULL;
		return (NULL);
	}
	line = findline(temp);
	res = final(res, temp, line);
	return (line);
}
