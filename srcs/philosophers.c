/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:10:20 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/18 06:59:04 by ctirions         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	data.error_type = init(&data, argv, argc);
	if (data.error_type)
		return (destroy_data(&data));
	pthread_mutex_lock(&data.end_m);
	pthread_mutex_unlock(&data.end_m);
	data.error_type = 6;
	return (destroy_data(&data));
}
