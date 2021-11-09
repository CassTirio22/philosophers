/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:28:56 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/09 18:34:49 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	take_forks(t_philos *philo)
{
	write(1, "yo\n", 3);
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
		take_forks(philo);/*
		make_eat(philo);
		make_sleep(philo);
		make_think(philo);*/
	}
	return (NULL);
}