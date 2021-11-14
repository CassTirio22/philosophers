/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 02:53:14 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/14 15:24:29 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	init_mutex(t_data *data)
{
	int	i;

	data->forks_m = (pthread_mutex_t *) \
	malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks_m)
		ft_error("Malloc error...", data);
	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks_m[i], NULL);
		pthread_mutex_init(&data->philos[i].eat_m, NULL);
	}
	pthread_mutex_init(&data->write_m, NULL);
	pthread_mutex_init(&data->end_m, NULL);
	pthread_mutex_lock(&data->end_m);
}

static void	init_philos(t_data *data)
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
			pthread_mutex_unlock(&data->end_m);
		usleep(100);
	}
}

static void	init_threads(t_data *data)
{
	int			i;
	pthread_t	tid;

	data->start = getime();
	i = -1;
	if (data->eat_count)
	{
		if (pthread_create(&tid, NULL, eat_count, (void *)data))
			ft_error("Thread error...\n", data);
		pthread_detach(tid);
	}
	while (++i < data->nb_philo)
	{
		if (pthread_create(&tid, NULL, \
		make_actions, (void *)(data->philos + i)))
			ft_error("Thread error...\n", data);
		usleep(100);
		pthread_detach(tid);
	}
}

void	init(t_data *data, char **argv, int argc)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->eat_count = ft_atoi(argv[5]);
	else
		data->eat_count = 0;
	if (!data->nb_philo || data->time_die < 60 || data->time_eat < 60 \
	|| data->time_sleep < 60 || data->eat_count < 0)
		ft_error("Bad arguments !", data);
	data->philos = (t_philos *)malloc(sizeof(t_philos) * data->nb_philo);
	if (!data->philos)
		ft_error("Malloc error...", data);
	init_philos(data);
	init_mutex(data);
	init_threads(data);
}
