#include "Philosophers.h"

int     ft_atoi(const char *arr)
{
	int     sign;
	int     res;

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

unsigned long time_init(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void init_data(t_data *data, char **argv, int argc)
{
	data->numbers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = 0;
	data->forks = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t) *
			data->numbers);
//	pthread_mutex_init(&data->voice, NULL);
	//check data;
}

void init_philosophers(t_philosophers **philosophers, t_data *data)
{
	int i = 0;

	while (i < data->numbers)
	{
		(*philosophers)[i].index = i + 1;
		if (i == 0)
			(*philosophers)[i].left_fork = data->numbers - 1;
		else
			(*philosophers)[i].left_fork = i - 1;
		(*philosophers)[i].right_fork = i;
		(*philosophers)[i].data = *data;
		(*philosophers)[i].number_of_times_eat = 0;
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void message(char *str, t_philosophers *philosophers)
{
	unsigned long time;

	time = time_init() - philosophers->data.start;
//	pthread_mutex_lock(&philosophers->data->voice);
	printf("%lu %d %s", time, philosophers->index, str);
//	pthread_mutex_unlock(&philosophers->data->voice);
}

void ft_usleep(int time)
{
	unsigned long end;

	end = time_init() + (unsigned long)time;
	while (time_init() < end)
		usleep(0);
}

void *start_simulation(void *philosophers)
{
	t_philosophers *philo;

	philo = (t_philosophers *)philosophers;
	philo->data.start = time_init();
	while (1)
	{
		pthread_mutex_lock(&philo->data.forks[philo->left_fork]);
		message("has taken a left fork\n", philo);
		pthread_mutex_lock(&philo->data.forks[philo->right_fork]);
		message("has taken a right fork\n", philo);
		message("is eating\n", philo);
		ft_usleep(philo->data.time_to_eat);
		pthread_mutex_unlock(&philo->data.forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data.forks[philo->right_fork]);
		message("is sleeping\n", philo);
		ft_usleep(philo->data.time_to_sleep);
		message("is thinking\n", philo);
	}
}

void init_threads(t_philosophers *philosophers, t_data *data)
{
	int i = 0;
	while (i < data->numbers)
	{
		pthread_create(&philosophers[i].t, NULL, start_simulation,
		(void *)&philosophers[i]);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < data->numbers)
	{
		pthread_join(philosophers[i].t, NULL);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_data data;
	t_philosophers *philosophers;

	philosophers = (t_philosophers *)malloc(data.numbers * sizeof(t_philosophers));
	init_data(&data, argv, argc);
	init_philosophers(&philosophers, &data);
	init_threads(philosophers, &data);
//	printf("%d %d %d %d %d\n", data.numbers, data.time_to_die,
//		   data.time_to_eat, data.time_to_sleep, data.number_of_times_each_philosopher_must_eat);
//	while (count < data.numbers)
//	{
//		printf("%d %d %d\n", philosophers[count].index, philosophers[count]
//		.left_fork, philosophers[count].right_fork);
//		count++;
//	}
	return (0);
}