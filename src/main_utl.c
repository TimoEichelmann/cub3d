/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:33:01 by snegi             #+#    #+#             */
/*   Updated: 2025/11/19 15:31:17 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_error(t_check_id *id, char *player, int *count)
{
	id->n = 0;
	id->s = 0;
	id->w = 0;
	id->e = 0;
	id->f = 0;
	id->c = 0;
	*player = '\0';
	count = 0;
}

void	error_check_print(t_check_id id, t_cubdata *cubdata)
{
	if (id.s == 0 || id.n == 0 || id.w == 0
		|| id.e == 0 || id.f == 0 || id.c == 0)
		err("map missing identifier\n", NULL, NULL);
	if (cubdata->firstposition == '\0')
		err("No player in map", NULL, NULL);
}

char	*ft_strdup1(char *s)
{
	int		i;
	char	*p;

	i = 0;
	while (s[i] && (s[i] != '\n' && s[i] != '\0'))
		i++;
	p = malloc(i + 1);
	if (!p)
		return (0);
	if (p == s)
		return (0);
	i = 0;
	while (s[i] && (s[i] != '\n' && s[i] != '\0'))
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strdup2(char *s)
{
	int		i;
	char	*p;

	i = 0;
	while (s[i] == ' ')
		i++;
	s = s + i;
	i = 0;
	while (s[i] && (s[i] != '\n' && s[i] != '\0'))
		i++;
	p = malloc(i + 1);
	if (!p)
		return (0);
	if (p == s)
		return (0);
	i = 0;
	while (s[i] && (s[i] != '\n' && s[i] != '\0'))
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int	ft_atoi1(const char *p)
{
	int	i;
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	i = 0;
	while (p[i] == ' ' || p[i] == '\f' || p[i] == '\n' || p[i] == '\r'
		|| p[i] == '\t' || p[i] == '\v')
		i++;
	while (p[i] && (p[i] != '\0' && p[i] != '\n'))
	{
		if (p[i] >= '0' && p[i] <= '9')
			result = result * 10 + (p[i] - '0');
		else
			return (-2);
		i++;
	}
	return (result * sign);
}
