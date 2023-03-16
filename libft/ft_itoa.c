/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:08:04 by lgyger            #+#    #+#             */
/*   Updated: 2021/10/27 18:23:44 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"ft_printf.h"

static long int		ft_countdigit(int n);
static char			*ft_f(char *s, unsigned long int n, unsigned int i);

char	*ft_itoa(int n)
{
	int			i;
	char		*string;
	long int	number;

	number = 0;
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
		string[0] = '-';
	}
	else
		number = n;
	string = ft_f(string, number, i);
	return (string);
}

static long int	ft_countdigit(int n)
{
	long int	b;

	b = 0;
	if (n <= 0)
		b = 1;
	while (n != 0)
	{
		b++;
		n = n / 10;
	}
	return (b);
}

static char	*ft_f(char *s, unsigned long int n, unsigned int i)
{
	while (n > 0)
	{
		s[i--] = 48 + (n % 10);
		n = n / 10;
	}
	return (s);
}
