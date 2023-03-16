/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexitoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:22:02 by lgyger            #+#    #+#             */
/*   Updated: 2021/10/27 18:24:31 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"ft_printf.h"
#include <stdlib.h>
#include <stdio.h>

static long int		ft_countdigit(unsigned long long int n);
static char			*ft_f(char *s, unsigned int n, int i);

char	*ft_hexitoa(unsigned int n)
{
	unsigned int			i;
	char					*string;
	unsigned int			number;

	string = NULL;
	i = ft_countdigit(n);
	string = (char *)malloc(sizeof(char) * (i + 1));
	if (!(string))
		return (NULL);
	string[i--] = '\0';
	if (n == 0)
		string[0] = '0';
	if (n < 0)
	{
		number = n;
		number *= -1;
	}
	else
		number = n;
	string = ft_f(string, number, i);
	return (string);
}

static long int	ft_countdigit(unsigned long long int n)
{
	long long int	b;

	b = 0;
	if (n <= 0)
		b = 1;
	while (n != 0)
	{
		b++;
		n = n / 16;
	}
	return (b);
}

static char	*ft_f(char *s, unsigned int n, int i)
{
	long int	a;

	while (n > 0)
	{
		a = n % 16;
		if (a < 10)
			s[i--] = 48 + (n % 16);
		else
			s[i--] = 55 + (n % 16);
		n = n / 16;
	}
	return (s);
}
