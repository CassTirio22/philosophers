/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:24:52 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/17 17:54:27 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	destroy_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_unlock(&data->forks_m[i]);
		pthread_mutex_destroy(&data->forks_m[i]);
	}
}

int	destroy_data(t_data *data)
{
	if (data->error_type == 1)
		return (1);
	else if (data->error_type == 2)
		free(data->philos);
	else if (data->error_type == 3)
		free(data->forks_m);
	else if (data->error_type == 4)
		destroy_forks(data);
	else if (data->error_type == 5)
	{
		pthread_mutex_unlock(&data->write_m);
		pthread_mutex_destroy(&data->write_m);
	}
	else if (data->error_type == 6)
	{
		pthread_mutex_unlock(&data->end_m);
		pthread_mutex_destroy(&data->end_m);
	}
	data->error_type--;
	destroy_data(data);
	return (1);
}

void	write_msg(t_philos *philo, char *msg, int is_dead)
{
	static int	finish = 0;

	pthread_mutex_lock(&philo->data->write_m);
	if (!finish)
	{
		if (is_dead)
			finish = 1;
		/*printf("%llu %d %s", getime() \
		- philo->data->start, philo->pos + 1, msg);*/
		ft_putnbr(getime() - philo->data->start);
		write(1, " ", 1);
		ft_putnbr(philo->pos + 1);
		write(1, " ", 1);
		ft_putstr(msg);
	}
	pthread_mutex_unlock(&philo->data->write_m);
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

// TO DELETE

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
