/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:33:01 by snegi             #+#    #+#             */
/*   Updated: 2024/07/12 13:18:26 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (p[i + 1] >= '0' && p[i + 1] <= '9' && (p[i] == '-' || p[i] == '+'))
	{
		if (p[i] == '-')
			sign = -1;
		i++;
	}
	else if ((p[i] == '-' || p[i] == '+') && !(p[i + 1] >= '0' && p[i] <= '9'))
		return (0);
	while (p[i] && (p[i] != '\0' && p[i] != '\n'))
	{
		if (p[i] >= '0' && p[i] <= '9')
			result = result * 10 + (p[i] - '0');
		else
			return(-2);
		i++;
	}
	return (result * sign);
}
