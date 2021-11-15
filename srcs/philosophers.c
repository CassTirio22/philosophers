/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:10:20 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/15 18:52:40 by ctirions         ###   ########.fr       */
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

void	write_msg(t_philos *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->write_m);
	printf("%lld %d %s", getime() - philo->data->start, philo->pos + 1, msg);
	pthread_mutex_unlock(&philo->data->write_m);
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
