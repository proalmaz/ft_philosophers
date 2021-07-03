/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vping <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 13:26:12 by vping             #+#    #+#             */
/*   Updated: 2021/07/03 13:26:14 by vping            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	message(char *str, t_philosophers *philosophers)
{
	unsigned long	time;

	time = time_init() - philosophers->data->start;
	pthread_mutex_lock(&philosophers->data->vs);
	printf("%lu %d %s", time, philosophers->index, str);
	pthread_mutex_unlock(&philosophers->data->vs);
}

void	*start_simulation(void *philosophers)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)philosophers;
	philo->data->start = time_init();
	philo->check = time_init() + philo->data->time_to_die;
	while (1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		message("has taken a left fork\n", philo);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		philo->check = time_init() + philo->data->time_to_die;
		message("has taken a right fork\n", philo);
		philo->eating = 1;
		message("is eating\n", philo);
		ft_usleep(philo->data->time_to_eat);
		philo->number_of_times_eat++;
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		philo->eating = 0;
		message("is sleeping\n", philo);
		ft_usleep(philo->data->time_to_sleep);
		message("is thinking\n", philo);
	}
}

int	check_life(t_philosophers *philosophers)
{
	if (time_init() >= philosophers->check
		&& philosophers->eating == 0)
		return (0);
	return (1);
}

int	check_end_of_loop(t_philosophers *philosophers, t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == philosophers->data->numbers)
			i = 0;
		if (!check_life(&philosophers[i]))
		{
			pthread_mutex_lock(&philosophers->data->vs);
			printf("%lu %d died\n", time_init() - philosophers[i].data->start,
				   philosophers[i].index);
			return (0);
		}
		while (philosophers[data->numbers - 1].number_of_times_eat
			   == philosophers->data->number_of_times_each_philosopher_must_eat
			   && philosophers->data->number_of_times_each_philosopher_must_eat
			   > 0)
			return (0);
		i++;
	}
}

int	init_threads(t_philosophers *philosophers, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numbers)
	{
		pthread_create(&philosophers[i].t, NULL, start_simulation, (void *)
			&philosophers[i]);
		pthread_detach(philosophers[i].t);
		usleep(100);
		i++;
	}
	if (!(check_end_of_loop(philosophers, data)))
		return (0);
	return (1);
}
