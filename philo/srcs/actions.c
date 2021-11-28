/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:28:56 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/28 15:02:29 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	slip(t_philos *philo)
{
	if (philo->data->is_dead)
		return ;
	write_msg(philo, "is sleeping\n", 0, CYAN);
	pthread_mutex_unlock(&philo->data->forks_m[philo->fork_left]);
	if (philo->data->is_dead)
		return ;
	pthread_mutex_unlock(&philo->data->forks_m[philo->fork_right]);
	msleep(philo->data->time_sleep);
	if (philo->data->is_dead)
		return ;
}

static void	eat(t_philos *philo)
{
	if (philo->data->is_dead)
		return ;
	philo->is_eating = 1;
	write_msg(philo, "is eating\n", 0, GREEN);
	philo->eat_count++;
	if (philo->data->is_dead)
		return ;
	philo->last_eat = getime();
	msleep(philo->data->time_eat);
	if (philo->data->is_dead)
		return ;
	philo->is_eating = 0;
}

static void	take_forks(t_philos *philo)
{
	if (philo->data->is_dead)
		return ;
	pthread_mutex_lock(&philo->data->forks_m[philo->fork_left]);
	write_msg(philo, "has taken a fork\n", 0, YELLOW);
	if (philo->data->is_dead)
		return ;
	pthread_mutex_lock(&philo->data->forks_m[philo->fork_right]);
	write_msg(philo, "has taken a fork\n", 0, YELLOW);
	if (philo->data->is_dead)
		return ;
}

static void	*dead(void *philo_v)
{
	t_philos	*philo;

	philo = (t_philos *)philo_v;
	while (1)
	{
		if (philo->data->is_dead)
			return (NULL);
		if (!philo->is_eating && \
		getime() > philo->last_eat + philo->data->time_die)
		{
			write_msg(philo, "died\n", 1, RED);
			philo->data->is_dead = 1;
			pthread_mutex_unlock(&philo->data->end_m);
			return (NULL);
		}
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
		if (philo->data->is_dead)
			return (NULL);
		eat(philo);
		if (philo->data->is_dead)
			return (NULL);
		slip(philo);
		write_msg(philo, "is thinking\n", 0, PURPLE);
	}
	return (NULL);
}
