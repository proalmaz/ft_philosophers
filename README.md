# Philo

This is the simple representation of solving [Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).

# Usage
## Philosophers should avoid dying

Run command below in your terminal
```
git clone https://github.com/proalmaz/ft_philosophers.git philo 
cd philo
make
```
Run tests for example:

./philo 5 800 200 200 5

./philo 10 1000 200 100

./philo 100 1000 100 100 10

To stop simulation type `CTRL + c` 

# Received arguments

Each program should have the same options:

1. number_of_philosophers;
2. time_to_die;
3. time_to_eat;
4. time_to_sleep;
5. number_of_times_each_philosopher_must_eat (optional);

# Algorithm

1. think until the left fork is available, when it is, pick it up

2. think until the right fork is available, when it is, pick it up

3. when both forks are held, eat for a fixed amount of time

4. then, put the right fork down

5. then, put the left fork down

6. repeat

`Deadlock` does not happen because all philosophers take the left fork first then the right fork and the last philosopher takes the right fork and then the left.
