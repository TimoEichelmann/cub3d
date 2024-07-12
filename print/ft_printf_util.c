/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snegi <snegi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:15:04 by snegi             #+#    #+#             */
/*   Updated: 2023/12/18 12:15:06 by snegi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printremaining(const char *s, int len, va_list list)
{
	while (*s != '%' && *s != '\0')
	{
		write(1, s++, 1);
		len++;
	}
	if (*s != '\0')
		len = findtype(s + 1, len, list);
	return (len);
}

int	printchar(int len, char c)
{
	write(1, &c, 1);
	len = len + 1;
	return (len);
}

int	printstring(int len, char *str)
{
	int	i;

	if (!str)
	{
		write(1, "(null)", 6);
		return (len + 6);
	}
	i = 0;
	while (str && str[i] != '\0')
		i++;
	len = len + i;
	write(1, str, i);
	return (len);
}

int	printnumber(int num, int len)
{
	char	c;

	if (num == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (len + 11);
	}
	else if (num < 0)
	{
		write(1, "-", 1);
		len = printnumber((num * -1), len);
	}
	else if (num > 9)
	{
		len = printnumber(num / 10, len);
		c = num % 10 + '0';
		write(1, &c, 1);
	}
	else
	{
		c = num + '0';
		write(1, &c, 1);
	}
	return (len + 1);
}
