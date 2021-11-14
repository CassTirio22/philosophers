/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:52:22 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/14 15:24:53 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	write_msg(t_philos *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->write_m);
	ft_putnbr(getime() - philo->data->start);
	write(1, " ", 1);
	ft_putnbr(philo->pos + 1);
	ft_putstr(msg);
	pthread_mutex_unlock(&philo->data->write_m);
}
