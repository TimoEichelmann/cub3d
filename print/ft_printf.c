/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snegi <snegi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:13:38 by snegi             #+#    #+#             */
/*   Updated: 2023/12/18 12:13:41 by snegi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	findtype(const char *s, int len, va_list list)
{
	size_t	num;

	if (*s == 'c')
		len = printchar(len, va_arg(list, int));
	else if (*s == 's')
		len = printstring(len, va_arg(list, char *));
	else if (*s == 'p')
	{
		num = va_arg(list, size_t);
		if (num >= 1)
			write (1, "0x", 2);
		len = printhpointer(len + 2, num);
	}
	else if (*s == 'd' || *s == 'i')
		len = printnumber(va_arg(list, int), len);
	else if (*s == 'u')
		len = printunsigned(len, va_arg(list, unsigned int));
	else if (*s == 'x')
		len = printhexa(len, va_arg(list, unsigned int), 'x');
	else if (*s == 'X')
		len = printhexa(len, va_arg(list, unsigned int), 'X');
	else if (*s == '%')
		len = printchar(len, '%');
	len = printremaining(++s, len, list);
	return (len);
}

int	ft_printf(const char *s, ...)
{
	va_list		list;
	int			len;

	if (!s)
		return (-1);
	len = 0;
	va_start(list, s);
	while (s[len] != '%' && s[len] != '\0')
		write(1, &s[len++], 1);
	if (s[len] == '%' && s[len] != '\0')
		len = findtype(&s[len + 1], len, list);
	va_end(list);
	return (len);
}
