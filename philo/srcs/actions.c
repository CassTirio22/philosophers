/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:28:56 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/23 15:40:53 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	slip(t_philos *philo)
{
	write_msg(philo, "is sleeping\n", 0, CYAN);
	pthread_mutex_unlock(&philo->data->forks_m[philo->fork_left]);
	pthread_mutex_unlock(&philo->data->forks_m[philo->fork_right]);
	msleep(philo->data->time_sleep);
}

static void	eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->live_m);
	philo->is_eating = 1;
	write_msg(philo, "is eating\n", 0, GREEN);
	philo->eat_count++;
	msleep(philo->data->time_eat);
	philo->last_eat = getime();
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->live_m);
}

static void	take_forks(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->forks_m[philo->fork_left]);
	write_msg(philo, "has taken a fork\n", 0, YELLOW);
	pthread_mutex_lock(&philo->data->forks_m[philo->fork_right]);
	write_msg(philo, "has taken a fork\n", 0, YELLOW);
}

static void	*dead(void *philo_v)
{
	t_philos	*philo;

	philo = (t_philos *)philo_v;
	while (1)
	{
		pthread_mutex_lock(&philo->live_m);
		if (!philo->is_eating && \
		getime() > philo->last_eat + philo->data->time_die)
		{
			write_msg(philo, "died\n", 1, RED);
			pthread_mutex_unlock(&philo->live_m);
			pthread_mutex_unlock(&philo->data->end_m);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->live_m);
		usleep(100);
	}
	return (NULL);
}

void	*make_actions(void *philo_v)
{
	t_philos	*philo;
	pthread_t	tid;

	philo = (t_philos *)philo_v;
	philo->last_eat = philo->data->start;
	if (pthread_create(&tid, NULL, &dead, philo_v))
		return (NULL);
	pthread_detach(tid);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		slip(philo);
		write_msg(philo, "is thinking\n", 0, PURPLE);
	}
	return (NULL);
}
