/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vping <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 13:13:07 by vping             #+#    #+#             */
/*   Updated: 2021/07/03 13:13:12 by vping            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_philosophers	*philo;

	if (!(init_data(&data, argv, argc)))
		return (free_data(&data));
	philo = (t_philosophers *)malloc(data.numbers * sizeof(t_philosophers));
	if (!philo)
		return (0);
	init_philosophers(&philo, &data);
	if (!(init_threads(philo, &data)))
		return (free_all(&data, &philo));
}
