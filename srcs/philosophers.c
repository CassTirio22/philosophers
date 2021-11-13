/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:10:20 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/13 18:23:29 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	free_data(t_data *data)
{
	if (!data)
		;
}

void	ft_error(char *str, t_data *data)
{
	printf("%s\n", str);
	free_data(data);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		ft_error("Bad arguments !", &data);
	init(&data, argv, argc);
	pthread_mutex_lock(&data.dead_m);
	pthread_mutex_unlock(&data.dead_m);
	return (0);
}