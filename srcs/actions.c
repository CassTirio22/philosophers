/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:28:56 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/08 18:40:29 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*make_actions(void *philo_v)
{
	t_philos	*philo;

	philo = (t_philos *)philo_v;
	while (1)
	{
		take_forks(philo);
		make_eat(philo);
		make_sleep(philo);
		make_think(philo);
	}
	return (NULL);
}