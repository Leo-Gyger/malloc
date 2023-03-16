/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgyger <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 19:35:19 by lgyger            #+#    #+#             */
/*   Updated: 2023/03/16 16:29:15 by lgyger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

void	ft_putchar(char c, int *p);
void	ft_putstr(char *str, int *p, int flag, int flag2);
char	*ft_itoa(int n);
char	*ft_uitoa(unsigned int n);
char	*ft_hexitoa(unsigned int n);
char	*ft_shexitoa(unsigned int n);
char	*ft_p(unsigned long long int n);
int		ft_printf(const char *str, ...);
void	*ft_memmove(void *dest, const void *src, size_t n);
#endif
