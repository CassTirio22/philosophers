/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:07:39 by ctirions          #+#    #+#             */
/*   Updated: 2021/11/28 13:27:12 by ctirions         ###   ########.fr       */
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

# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define ORANGE "\033[34m"
# define PURPLE "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define RESET "\033[0m"

typedef struct s_data	t_data;

typedef struct s_philos
{
	int					is_eating;
	int					fork_left;
	int					fork_right;
	int					eat_count;
	int					pos;
	t_data				*data;
	unsigned long long	last_eat;
}				t_philos;

struct	s_data
{
	int					is_dead;
	int					error_type;
	int					eat_count;
	int					nb_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	t_philos			*philos;
	pthread_mutex_t		*forks_m;
	pthread_mutex_t		write_m;
	pthread_mutex_t		end_m;
	unsigned long long	start;
};

int					destroy_data(t_data *data);
void				write_msg(t_philos *philo, char *msg, \
					int is_dead, char *color);
unsigned long long	getime(void);
int					init(t_data *data, char **argv, int argc);
int					init_threads(t_data *data);
void				*make_actions(void *philo_v);
int					ft_atoi(char *str);
void				ft_putstr(char *str);
void				ft_putnbr(unsigned long long n);
void				msleep(unsigned long long ms);

#endif