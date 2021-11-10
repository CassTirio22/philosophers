/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:28:56 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/10 18:02:30 by ctirions         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->eat_m);
	philo->last_eat = getime();
	write_msg(philo, " is eating\n");
	philo->eat_count++;
	usleep(1000 * philo->data->time_eat);
	pthread_mutex_unlock(&philo->eat_m);
}

static void	take_forks(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->forks_m[philo->fork_left]);
	write_msg(philo, " has taken a fork\n");
	pthread_mutex_lock(&philo->data->forks_m[philo->fork_right]);
	write_msg(philo, " has taken a fork\n");
}

void	*make_actions(void *philo_v)
{
	t_philos	*philo;

	philo = (t_philos *)philo_v;
	while (1)
	{
		take_forks(philo);
		eat(philo);
		slip(philo);
		write_msg(philo, " is thinking\n");
	}
	return (NULL);
}