/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 02:53:14 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/04 19:26:01 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void init_mutex(t_data *data)
{
    int i;

    data->forks = (pthread_mutex_t *)malloc(sizeof(*(data->forks)) \
    * data->nb_philo);
    if (!data->forks)
        ft_error("Malloc error...", data);
    i = -1;
    while (++i < data->nb_philo)
        pthread_mutex_init(&data->forks[i], NULL);
}

static void init_philos(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->nb_philo)
    {
        data->philos[i]->start_eat = 0;
        data->philos[i]->pos = i;
        data->philos[i]->fork_left = i;
        data->philos[i]->fork_right = (i + 1) % data->nb_philo;
        data->philos[i]->eat_count = 0;
        data->philos[i]->data = data;
        pthread_mutex_init(&data->philos[i]->eat_m, NULL);
        pthread_mutex_lock(&data->philos[i]->eat_m);
    }
}

void    init(t_data *data)
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
    || !data->time_sleep < 60 || data->eat_count < 0)
		ft_error("Bad arguments !", data);
    data->forks = NULL;
    data->philos = NULL;
    data->philos = (t_philos *)malloc(sizeof(*(data->philos)) * data->nb_philo);
    if (!data->philos)
        ft_error("Malloc error...", data);
    init_philos(data);
    init_mutex(data);
}
