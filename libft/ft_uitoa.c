/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                          :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:08:04 by lgyger            #+#    #+#             */
/*   Updated: 2021/10/27 19:37:53 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

static unsigned int		ft_countdigit(unsigned int n);
static char				*ft_f(char *s, unsigned long int n, unsigned int i);

char	*ft_uitoa(unsigned int n)
{
	unsigned int			i;
	char					*string;
	unsigned int			number;

	number = 0;
	string = NULL;
	i = ft_countdigit(n);
	string = (char *)malloc(sizeof(char) * (i + 1));
	if (!(string))
		return (NULL);
	string[i--] = '\0';
	if (n == 0)
		string[0] = '0';
	number = n;
	string = ft_f(string, number, i);
	return (string);
}

static unsigned int	ft_countdigit(unsigned int n)
{
	int	b;

	b = 0;
	if (n == 0)
		b++;
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
