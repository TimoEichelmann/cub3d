/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snegi <snegi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:13:47 by snegi             #+#    #+#             */
/*   Updated: 2023/12/18 12:13:50 by snegi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stddef.h>

int	ft_printf(const char *s, ...);
int	printchar(int len, char c);
int	findtype(const char *s, int len, va_list list);
int	printstring(int len, char *str);
int	printnumber(int num, int len);
int	printremaining(const char *s, int len, va_list list);
int	printunsigned(int len, unsigned int num);
int	printhexa(int len, unsigned int num, char x);
int	printhpointer(int len, size_t num);

#endif
