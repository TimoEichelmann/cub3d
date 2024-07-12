/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fun.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snegi <snegi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:46:43 by snegi             #+#    #+#             */
/*   Updated: 2023/12/18 12:46:46 by snegi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printunsigned(int len, unsigned int num)
{
	char	c;

	if (num > 9)
		len = printunsigned(len, num / 10);
	c = num % 10 + '0';
	write(1, &c, 1);
	return (len + 1);
}

int	printhexa(int len, unsigned int num, char x)
{
	char	*base;
	char	c;

	if (x == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (num >= 16)
		len = printhexa(len, num / 16, x);
	c = base[num % 16];
	write(1, &c, 1);
	return (len + 1);
}

int	printhpointer(int len, size_t num)
{
	char		*base;	
	char		c;

	base = "0123456789abcdef";
	if (num < 1)
	{
		write (1, "(nil)", 5);
		return (len + 3);
	}
	if (num > 15)
		len = printhpointer(len, num / 16);
	c = base[num % 16];
	write(1, &c, 1);
	return (len + 1);
}
