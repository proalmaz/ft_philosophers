/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vping <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 13:29:41 by vping             #+#    #+#             */
/*   Updated: 2021/07/03 13:29:42 by vping            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	int				numbers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	unsigned long	start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	vs;
}	t_data;

typedef struct s_philosophers
{
	t_data			*data;
	pthread_t		t;
	int				index;
	int				right_fork;
	int				left_fork;
	int				number_of_times_eat;
	unsigned long	check;
	int				eating;
}	t_philosophers;

int				ft_atoi(const char *arr);

int				ft_isdigit_str(const char *str);

int				init_data(t_data *data, char **argv, int argc);

void			init_philosophers(t_philosophers **philosophers, t_data *data);

int				check_data(t_data *data);

void			ft_usleep(int time);

unsigned long	time_init(void);

int				free_data(t_data *data);

int				free_all(t_data *data, t_philosophers **philosophers);

int				init_threads(t_philosophers *philosophers, t_data *data);

int				check_life(t_philosophers *philosophers);

void			*start_simulation(void *philosophers);

void			message(char *str, t_philosophers *philosophers);

int				check_end_of_loop(t_philosophers *philosophers, t_data *data);

#endif
