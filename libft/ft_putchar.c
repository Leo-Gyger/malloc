/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:10:24 by lgyger            #+#    #+#             */
/*   Updated: 2021/10/27 18:00:47 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

void	ft_putstr(char *c, int *p, int flag, int flag2);

void	ft_putchar(char c, int *p)
{
	write(1, &c, 1);
	*p += 1;
}

void	ft_putstr(char *c, int *p, int flag, int flag2)
{
	unsigned int	i;
	int				e;

	e = 0;
	if (!c)
		c = "(null)";
	i = 0;
	while (c[i] != '\0')
	{
		if (e != 4 && flag2 == 1 && (c[i] == 'f'
				|| c[i] == 'F'))
		{
			e++;
			i++;
		}
		else
			ft_putchar(c[i], p);
		i++;
	}
	if (flag == 1)
		free(c);
}
