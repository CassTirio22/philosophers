/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:07:39 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/08 16:42:48 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_data	t_data;

typedef struct	s_philos
{
	int 			start_eat;
	int				fork_left;
	int				fork_right;
	int				eat_count;
	int				pos;
	t_data 			*data;
	pthread_mutex_t	eat_m;
}					t_philos;

struct	s_data
{
	int				eat_count;
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	t_philos		*philos;
	pthread_mutex_t	*forks_m;
	pthread_mutex_t write_m;
	pthread_mutex_t dead_m;
};

typedef struct s_render
{
	pthread_t	*threads;
	t_philos	*philos;
}				t_render;

int		ft_atoi(char *str);
void	ft_error(char *str, t_data *data);

#endif