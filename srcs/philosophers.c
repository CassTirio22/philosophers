/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:10:20 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/03 18:39:28 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	free_data(t_data *data)
{
	if (!data)
		;
}

static void	arg_error(int argc, char **argv, t_data *data)
{
	if (argc < 5)
		ft_error(0, data);
	data->nb_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (!data->nb_philo || !data->time_die || !data->time_eat || !data->time_sleep)
		ft_error(0, data);
	data->forks = (int *)malloc(sizeof(int) * data->nb_philo);
	if (!data->forks)
		ft_error(0, data);
	memset(data->forks, 1, data->nb_philo);
}

void	ft_error(int flag, t_data *data)
{
	if (!flag)
		printf("Error\n");
	free_data(data);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	arg_error(argc, argv, &data);
	return (0);
}