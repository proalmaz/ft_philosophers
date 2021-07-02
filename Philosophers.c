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

int ft_isdigit_str(const char *str)
{
	int i;

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

unsigned long time_init(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int check_data(t_data *data)
{
	if (data->numbers <= 0)
	{
		printf("Wrong number of philosophers\n");
		return (0);
	}
	return (1);
}

int init_data(t_data *data, char **argv, int argc)
{
	if (!ft_isdigit_str(argv[1]) || !ft_isdigit_str(argv[2]) ||
	!ft_isdigit_str(argv[3]) || !ft_isdigit_str(argv[4]))
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
	data->forks = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t) *
			data->numbers);
	pthread_mutex_init(&data->vs, NULL);
	if (!check_data(data))
		return (0);
	return (1);
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
		(*philosophers)[i].data = data;
		(*philosophers)[i].number_of_times_eat = 0;
		(*philosophers)[i].eating = 0;
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void message(char *str, t_philosophers *philosophers)
{
	unsigned long time;

	time = time_init() - philosophers->data->start;
	pthread_mutex_lock(&philosophers->data->vs);
	printf("%lu %d %s", time, philosophers->index, str);
	pthread_mutex_unlock(&philosophers->data->vs);
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

int check_life(t_philosophers *philosophers)
{
	if (time_init() >= philosophers->check &&
		philosophers->eating == 0)
		return (0);
	return (1);
}

int init_threads(t_philosophers *philosophers, t_data *data)
{
	int i = 0;

	while (i < data->numbers)
	{
		pthread_create(&philosophers[i].t, NULL, start_simulation,
		(void *)&philosophers[i]);
		pthread_detach(philosophers[i].t);
		usleep(100);
		i++;
	}
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
		while (philosophers[data->numbers - 1].number_of_times_eat ==
		philosophers->data->number_of_times_each_philosopher_must_eat &&
		philosophers->data->number_of_times_each_philosopher_must_eat > 0)
			return (0);
		i++;
	}
}

int free_data(t_data *data)
{
	int i;

	i = 0;
	while (i < data->numbers - 1)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	return (0);
}

int free_all(t_data *data, t_philosophers **philosophers)
{
	free_data(data);
	free(*philosophers);
	return (0);
}

int main(int argc, char **argv)
{
	t_data data;
	t_philosophers *philosophers;

	if (!(init_data(&data, argv, argc)))
		return (free_data(&data));
	philosophers = (t_philosophers *)malloc(data.numbers * sizeof(t_philosophers));
	if (!philosophers)
		return (0);
	init_philosophers(&philosophers, &data);
	if (!(init_threads(philosophers, &data)))
		return (free_all(&data, &philosophers));
}