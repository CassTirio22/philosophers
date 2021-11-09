/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:24:52 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/09 18:01:24 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

void	ft_putnbr(int nbr)
{
	unsigned int	nb;

	if (nbr < 0)
	{
		write(1, "-", 1);
		nb = -nbr;
	}
	else
		nb = nbr;
	if (nbr > 9)
		ft_putnbr(nbr / 10);
	ft_putchar(nbr % 10 + '0');
}

unsigned long long	getime(void)
{
	unsigned long long	res;
	struct timeval		time;

	gettimeofday(&time, NULL);
	res = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (res);
}

int	ft_atoi(char *str)
{
	int	sign;
	int	res;
	int	i;

	i = 0;
	sign = 1;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	if (str[i])
		return (0);
	return (res * sign);
}