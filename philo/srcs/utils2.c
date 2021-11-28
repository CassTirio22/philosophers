/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 13:23:09 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/28 13:26:40 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	msleep(unsigned long long ms)
{
	unsigned long long	begin;
	unsigned long long	end;

	begin = getime();
	end = begin;
	while (end - begin < ms)
	{
		usleep(100);
		end = getime();
	}
}

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	if (!str)
		write(1, "(null)", 6);
	while (str[++i])
		write(1, &str[i], 1);
}

void	ft_putnbr(unsigned long long n)
{
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}
