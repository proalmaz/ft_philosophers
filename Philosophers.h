#ifndef FT_PHILOSOPHERS_PHILOSOPHERS_H
#define FT_PHILOSOPHERS_PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_data
{
	int numbers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	unsigned long start;
	pthread_mutex_t *forks;
//	pthread_mutex_t vs;
}				t_data;

typedef struct	s_philosophers
{
	t_data data;
	pthread_t t;
	int index;
	int right_fork;
	int left_fork;
	int number_of_times_eat;
}				t_philosophers;


void hello(void);

#endif //FT_PHILOSOPHERS_PHILOSOPHERS_H
