/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vping <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 13:18:03 by vping             #+#    #+#             */
/*   Updated: 2021/07/03 13:18:05 by vping            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	check_data(t_data *data)
{
	if (data->numbers <= 0)
	{
		printf("Wrong number of philosophers\n");
		return (0);
	}
	return (1);
}

int	init_data(t_data *data, char **argv, int argc)
{
	if (!ft_isdigit_str(argv[1]) || !ft_isdigit_str(argv[2])
		|| !ft_isdigit_str(argv[3]) || !ft_isdigit_str(argv[4]))
	{
		printf("Some argument isn't digit or negative digit\n");
		return (0);
	}
	data->numbers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = 0;
	data->forks = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t)
			* data->numbers);
	pthread_mutex_init(&data->vs, NULL);
	if (!check_data(data))
		return (0);
	return (1);
}

void	init_philosophers(t_philosophers **philosophers, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numbers)
	{
		(*philosophers)[i].index = i + 1;
		if (i == 0)
			(*philosophers)[i].left_fork = data->numbers - 1;
		else
			(*philosophers)[i].left_fork = i - 1;
		(*philosophers)[i].right_fork = i;
		(*philosophers)[i].data = data;
		(*philosophers)[i].number_of_times_eat = 0;
		(*philosophers)[i].eating = 0;
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}
