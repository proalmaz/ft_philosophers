/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vping <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 13:16:04 by vping             #+#    #+#             */
/*   Updated: 2021/07/03 13:16:05 by vping            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

unsigned long	time_init(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int time)
{
	unsigned long	end;

	end = time_init() + (unsigned long)time;
	while (time_init() < end)
		usleep(0);
}

int	ft_atoi(const char *arr)
{
	int	sign;
	int	res;

	res = 0;
	sign = 1;
	while (*arr == ' ' || *arr == '\t' || *arr == '\v' || *arr == '\f'
		   || *arr == '\r' || *arr == '\n')
		arr++;
	if (*arr == '-' || *arr == '+')
	{
		if (*arr == '-')
			sign = -1;
		arr++;
	}
	while (*arr >= '0' && *arr <= '9')
	{
		res = res * 10 + (*arr - '0');
		arr++;
	}
	return (sign * res);
}

int	ft_isdigit_str(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}
