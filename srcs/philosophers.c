/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:10:20 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/15 16:41:07 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	destroy_data(t_data *data)
{
	int	i;

	i = -1;
	if (data->philos)
		free(data->philos);
	if (data->forks_m)
	{
		while (++i < data->nb_philo)
		{
			pthread_mutex_init(&data->forks_m[i], NULL);
			pthread_mutex_destroy(&data->forks_m[i]);
		}
		free(data->forks_m);
	}
	if (&data->write_m)
		pthread_mutex_destroy(&data->write_m);
	if (&data->end_m)
	pthread_mutex_destroy(&data->end_m);
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
	if (init(&data, argv, argc))
		return (destroy_data(&data));
	pthread_mutex_lock(&data.end_m);
	pthread_mutex_unlock(&data.end_m);
	return (destroy_data(&data));
}
