/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vping <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 13:26:49 by vping             #+#    #+#             */
/*   Updated: 2021/07/03 13:26:50 by vping            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->numbers - 1)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	return (0);
}

int	free_all(t_data *data, t_philosophers **philosophers)
{
	free_data(data);
	free(*philosophers);
	return (0);
}
