/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:55:37 by lgyger            #+#    #+#             */
/*   Updated: 2021/10/27 18:23:11 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

void			str_chr(char c, va_list arg, int *size);

int	ft_printf(const char *str, ...)
{
	int						size;
	va_list					arg;
	long long unsigned int	a;

	size = 0;
	va_start(arg, str);
	while (*str != '\0')
	{
		if (*str == '%')
		{
			str++;
			str_chr (*str, arg, &size);
			if (*str == 'p')
			{
				ft_putstr ("0x", &size, 0, 0);
				a = (unsigned long long int)(va_arg(arg, void *));
				ft_putstr(ft_p(a), &size, 1, 0);
			}
		}
		else
			ft_putchar(*str, &size);
		str++;
	}
	va_end(arg);
	return (size);
}

void	str_chr(char c, va_list arg, int *size)
{
	if (c == 'c')
		ft_putchar((char)va_arg(arg, char *), size);
	else if (c == 's')
		ft_putstr(va_arg(arg, char *), size, 0, 0);
	else if (c == 'i' || c == 'd')
		ft_putstr(ft_itoa(va_arg(arg, int)), size, 1, 0);
	else if (c == 'x')
		ft_putstr(ft_shexitoa(va_arg(arg, int)), size, 1, 0);
	else if (c == 'X')
		ft_putstr(ft_hexitoa(va_arg(arg, int)), size, 1, 0);
	else if (c == '%')
		ft_putchar('%', size);
	else if (c == 'u')
		ft_putstr(ft_uitoa(va_arg(arg, unsigned int)), size, 1, 0);
}
