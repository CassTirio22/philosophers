/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 02:53:14 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/28 14:54:42 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	init_mutex(t_data *data)
{
	int	i;

	data->forks_m = (pthread_mutex_t *) \
	malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks_m)
		return (2);
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks_m[i], NULL))
		{
			while (i--)
				pthread_mutex_destroy(&data->forks_m[i]);
			return (3);
		}
	}
	if (pthread_mutex_init(&data->write_m, NULL))
		return (4);
	if (pthread_mutex_init(&data->end_m, NULL))
		return (5);
	pthread_mutex_lock(&data->end_m);
	return (init_threads(data));
}

static int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philos[i].pos = i;
		data->philos[i].is_eating = 0;
		data->philos[i].fork_left = i;
		data->philos[i].fork_right = (i + 1) % data->nb_philo;
		data->philos[i].eat_count = 0;
		data->philos[i].data = data;
	}
	return (init_mutex(data));
}

static void	*eat_count(void *data_v)
{
	t_data	*data;
	int		count;
	int		i;

	data = (t_data *)data_v;
	while (1)
	{
		i = -1;
		count = 0;
		while (++i < data->nb_philo)
			if (data->philos[i].eat_count >= data->eat_count)
				count++;
		if (count == data->nb_philo)
		{
			write_msg(&data->philos[0], "", 2, NULL);
			data->is_dead = 1;
			usleep(100);
			pthread_mutex_unlock(&data->end_m);
		}
		usleep(100);
	}
	return (NULL);
}

int	init_threads(t_data *data)
{
	int			i;
	pthread_t	tid;

	data->start = getime();
	i = -1;
	if (data->eat_count)
	{
		if (pthread_create(&tid, NULL, &eat_count, (void *)data))
			return (6);
		pthread_detach(tid);
	}
	while (++i < data->nb_philo)
	{
		if (pthread_create(&tid, NULL, \
		&make_actions, (void *)(data->philos + i)))
			return (6);
		pthread_detach(tid);
		usleep(100);
	}
	return (0);
}

int	init(t_data *data, char **argv, int argc)
{
	data->forks_m = NULL;
	data->philos = NULL;
	data->nb_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->is_dead = 0;
	if (argc == 6)
		data->eat_count = ft_atoi(argv[5]);
	if (argc == 6 && !data->eat_count)
		return (1);
	if (argc == 5)
		data->eat_count = 0;
	if (!data->nb_philo || data->nb_philo > 200 || data->time_die < 60 || \
	data->time_eat < 60 || data->time_sleep < 60 || data->eat_count < 0)
		return (1);
	data->philos = (t_philos *)malloc(sizeof(t_philos) * data->nb_philo);
	if (!data->philos)
		return (1);
	return (init_philos(data));
}
