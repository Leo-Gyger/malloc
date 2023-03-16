/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                            :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:43:19 by lgyger            #+#    #+#             */
/*   Updated: 2021/10/27 18:25:41 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"ft_printf.h"

static long int		ft_countdigit(unsigned long long int n);
static char			*ft_f(char *s, unsigned long int n, unsigned long int i);

char	*ft_p(long long unsigned int n)
{
	long long unsigned int			i;
	char							*string;
	long long unsigned int			number;

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
	while (n != 0)
	{
		b++;
		n = n / 16;
	}
	return (b);
}

static char	*ft_f(char *s, unsigned long int n, unsigned long int i)
{
	long int	a;

	while (n > 0)
	{
		a = n % 16;
		if (a < 10)
			s[i--] = 48 + (n % 16);
		else
			s[i--] = 87 + (n % 16);
		n = n / 16;
	}
	return (s);
}
