/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:28:56 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/15 17:04:08 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	slip(t_philos *philo)
{
	write_msg(philo, " is sleeping\n");
	pthread_mutex_unlock(&philo->data->forks_m[philo->fork_left]);
	pthread_mutex_unlock(&philo->data->forks_m[philo->fork_right]);
	usleep(1000 * philo->data->time_sleep);
}

static void	eat(t_philos *philo)
{
	philo->is_eating = 1;
	philo->last_eat = getime();
	write_msg(philo, " is eating\n");
	philo->eat_count++;
	usleep(1000 * philo->data->time_eat);
	philo->is_eating = 0;
}

static void	take_forks(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->forks_m[philo->fork_left]);
	write_msg(philo, " has taken a fork\n");
	pthread_mutex_lock(&philo->data->forks_m[philo->fork_right]);
	write_msg(philo, " has taken a fork\n");
}

static void	*dead(void *philo_v)
{
	t_philos	*philo;

	philo = (t_philos *)philo_v;
	while (1)
	{
		if (!philo->is_eating && \
		getime() > philo->last_eat + philo->data->time_die)
		{
			write_msg(philo, " died\n");
			pthread_mutex_unlock(&philo->data->end_m);
		}
		usleep(100);
	}
}

void	*make_actions(void *philo_v)
{
	t_philos	*philo;
	pthread_t	tid;

	philo = (t_philos *)philo_v;
	philo->last_eat = philo->data->start;
	if (pthread_create(&tid, NULL, &dead, philo_v))
		return (NULL);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		slip(philo);
		write_msg(philo, " is thinking\n");
	}
	return (NULL);
}
